"""
Naive Bayes Classifier Implementation for Iris Dataset
Following assignment specifications with improvements

@author Chidera Izuora
@date 02/07/2026
"""

import numpy as np
import math
import os
import sys

# ============================================================================
# GAUSSIAN PROBABILITY FUNCTION WITH ROBUSTNESS
# ============================================================================

def gaussian_probability(x, mean, std):
    """
    Calculate probability using Gaussian distribution
    P(x) = (1 / sqrt(2*pi*sigma^2)) * exp(-(x-mu)^2 / (2*sigma^2))
    """
    # Handle zero variance by adding small epsilon
    if std <= 0:
        std = 1e-10
    
    exponent = np.exp(-((x - mean) ** 2) / (2 * std ** 2))
    coefficient = 1 / (np.sqrt(2 * np.pi) * std)
    return coefficient * exponent


# ============================================================================
# LOAD DATA WITH ERROR HANDLING
# ============================================================================

def load_data(filename):
    """
    Load dataset from file with error handling
    """
    if not os.path.exists(filename):
        print(f"Error: File '{filename}' not found.")
        sys.exit(1)
    
    try:
        data = np.loadtxt(filename)
        if data.size == 0:
            print(f"Error: File '{filename}' is empty.")
            sys.exit(1)
        return data
    except Exception as e:
        print(f"Error loading {filename}: {e}")
        sys.exit(1)


# ============================================================================
# NAIVE BAYES CLASSIFIER
# ============================================================================

def naive_bayes_classifier(training_data, testing_data):
    """
    Main Naive Bayes classifier function
    Returns predictions and probabilities
    """
    # Extract dimensions
    n_train = training_data.shape[0]
    d = training_data.shape[1] - 1  # Number of features
    
    # Separate features and labels
    X_train = training_data[:, :d]
    y_train = training_data[:, d]
    
    X_test = testing_data[:, :d]
    y_test = testing_data[:, d]
    
    # Separate data by class
    positive_mask = y_train == 1
    negative_mask = y_train == -1
    
    X_positive = X_train[positive_mask]
    X_negative = X_train[negative_mask]
    
    # Calculate prior probabilities
    n_positive = X_positive.shape[0]
    n_negative = X_negative.shape[0]
    n_total = n_train
    
    P_positive = n_positive / n_total
    P_negative = n_negative / n_total
    
    # Calculate mean and standard deviation for each class
    # Using ddof=1 for sample standard deviation
    mean_positive = np.mean(X_positive, axis=0)
    std_positive = np.std(X_positive, axis=0, ddof=1)
    
    mean_negative = np.mean(X_negative, axis=0)
    std_negative = np.std(X_negative, axis=0, ddof=1)
    
    # Handle zero standard deviation
    std_positive[std_positive == 0] = 1e-10
    std_negative[std_negative == 0] = 1e-10
    
    # Initialize arrays for predictions and probabilities
    predictions = np.zeros(y_test.shape)
    prob_positive = np.zeros(y_test.shape)
    prob_negative = np.zeros(y_test.shape)
    
    # Classify each test sample
    for i in range(y_test.shape[0]):
        sample = X_test[i]
        
        # Calculate log probabilities for both classes
        log_prob_pos = np.log(P_positive)
        log_prob_neg = np.log(P_negative)
        
        # Calculate likelihood for each feature
        for j in range(d):
            # Positive class
            feature_prob = gaussian_probability(sample[j], mean_positive[j], std_positive[j])
            log_prob_pos += np.log(feature_prob + 1e-100)  # Add tiny value to avoid log(0)
            
            # Negative class
            feature_prob = gaussian_probability(sample[j], mean_negative[j], std_negative[j])
            log_prob_neg += np.log(feature_prob + 1e-100)
        
        # Store probabilities (convert back from log)
        prob_positive[i] = np.exp(log_prob_pos)
        prob_negative[i] = np.exp(log_prob_neg)
        
        # Make prediction
        if log_prob_pos > log_prob_neg:
            predictions[i] = 1
        else:
            predictions[i] = -1
    
    return predictions, prob_positive, prob_negative, y_test


# ============================================================================
# EVALUATION METRICS
# ============================================================================

def calculate_metrics(predictions, true_labels):
    """
    Calculate all required evaluation metrics
    """
    # Ensure both arrays have the same type for comparison
    predictions = predictions.astype(int)
    true_labels = true_labels.astype(int)
    
    # Calculate confusion matrix
    tp = np.sum((predictions == 1) & (true_labels == 1))
    fp = np.sum((predictions == 1) & (true_labels == -1))
    tn = np.sum((predictions == -1) & (true_labels == -1))
    fn = np.sum((predictions == -1) & (true_labels == 1))
    
    # Calculate metrics
    accuracy = (tp + tn) / (tp + fp + tn + fn)
    
    precision = tp / (tp + fp) if (tp + fp) > 0 else 0
    recall = tp / (tp + fn) if (tp + fn) > 0 else 0
    
    f1_score = 2 * (precision * recall) / (precision + recall) if (precision + recall) > 0 else 0
    
    return {
        'tp': int(tp), 'fp': int(fp), 'tn': int(tn), 'fn': int(fn),
        'accuracy': accuracy, 'precision': precision,
        'recall': recall, 'f1_score': f1_score
    }


# ============================================================================
# DISPLAY RESULTS
# ============================================================================

def display_results(dataset_name, metrics):
    """
    Display results in a formatted way
    """
    print(f"\n{'='*60}")
    print(f"DATASET: {dataset_name}")
    print(f"{'='*60}")
    
    print(f"Training samples loaded successfully")
    print(f"Testing samples loaded successfully")
    
    print(f"\nRESULTS:")
    print(f"{'-'*60}")
    
    # Confusion Matrix
    print("\nConfusion Matrix:")
    print("                     PREDICTED")
    print("                 +------------+------------+")
    print("                 |  Positive  |  Negative  |")
    print("       ----------+------------+------------+")
    print(f" ACTUAL Positive | TP = {metrics['tp']:3d}    | FN = {metrics['fn']:3d}    |")
    print("                 +------------+------------+")
    print(f"        Negative | FP = {metrics['fp']:3d}    | TN = {metrics['tn']:3d}    |")
    print("                 +------------+------------+")
    
    print("\nDetailed Statistics:")
    print(f"  True Positives (TP):  {metrics['tp']}")
    print(f"  False Positives (FP): {metrics['fp']}")
    print(f"  True Negatives (TN):  {metrics['tn']}")
    print(f"  False Negatives (FN): {metrics['fn']}")
    
    print(f"\nPerformance Metrics:")
    print(f"  Accuracy:  {metrics['accuracy']:.4f} ({metrics['accuracy']*100:.2f}%)")
    print(f"  Precision: {metrics['precision']:.4f}")
    print(f"  Recall:    {metrics['recall']:.4f}")
    print(f"  F1-Score:  {metrics['f1_score']:.4f}")
    
    return metrics


# ============================================================================
# MAIN EXECUTION FUNCTION
# ============================================================================

def run_naive_bayes_pipeline(training_file, testing_file, dataset_name):
    """
    Complete pipeline for Naive Bayes classification
    """
    # Load data
    training_data = load_data(training_file)
    testing_data = load_data(testing_file)
    
    # Run classifier
    predictions, prob_pos, prob_neg, true_labels = naive_bayes_classifier(training_data, testing_data)
    
    # Calculate metrics
    metrics = calculate_metrics(predictions, true_labels)
    
    # Display results
    display_results(dataset_name, metrics)
    
    return metrics, predictions, true_labels


# ============================================================================
# MAIN PROGRAM
# ============================================================================

def main():
    print(f"{'='*60}")
    print("NAIVE BAYES CLASSIFIER - IRIS DATASET")
    print(f"{'='*60}")
    print("\nThis program implements the Naive Bayes algorithm with Gaussian")
    print("distribution for continuous features.")
    print(f"{'='*60}")
    
    # Define datasets to process
    datasets = [
        {
            'name': 'IRIS (4 features)',
            'train_file': 'irisTraining.txt',
            'test_file': 'irisTesting.txt'
        },
        {
            'name': 'IRIS PC (2 features from PCA)',
            'train_file': 'irisPCTraining.txt',
            'test_file': 'irisPCTesting.txt'
        }
    ]
    
    results = {}
    
    # Process each dataset
    for dataset in datasets:
        try:
            print(f"\nProcessing {dataset['name']}...")
            metrics, predictions, true_labels = run_naive_bayes_pipeline(
                dataset['train_file'],
                dataset['test_file'],
                dataset['name']
            )
            results[dataset['name']] = metrics
        except Exception as e:
            print(f"Error processing {dataset['name']}: {e}")
            continue
    
    # Display summary
    if results:
        print(f"\n{'='*60}")
        print("SUMMARY OF RESULTS")
        print(f"{'='*60}")
        
        for dataset_name, metrics in results.items():
            print(f"\n{dataset_name}:")
            print(f"  Accuracy:  {metrics['accuracy']:.4f} ({metrics['accuracy']*100:.2f}%)")
            print(f"  Precision: {metrics['precision']:.4f}")
            print(f"  Recall:    {metrics['recall']:.4f}")
            print(f"  F1-Score:  {metrics['f1_score']:.4f}")
            print(f"  TP={metrics['tp']}, FP={metrics['fp']}, TN={metrics['tn']}, FN={metrics['fn']}")
    
    print(f"\n{'='*60}")
    print("PROGRAM COMPLETED SUCCESSFULLY")
    print(f"{'='*60}")


# ============================================================================
# EXECUTION
# ============================================================================

if __name__ == "__main__":
    
    # Run with default datasets
    main()