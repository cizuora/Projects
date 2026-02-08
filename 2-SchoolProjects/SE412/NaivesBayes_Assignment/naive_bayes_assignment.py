"""
Naive Bayes Classifier Implementation
Following the assignment skeleton structure
Tests on both Iris and Iris PC datasets

@author Chidera Izuora
@date  02/07/2026
"""

import numpy
import math

# ============================================================================
# GAUSSIAN PROBABILITY FUNCTION
# ============================================================================

def gaussian_probability(x, mean, std):
    """
    Calculate probability using Gaussian distribution
    P(x) = (1 / sqrt(2*pi*sigma^2)) * exp(-(x-mu)^2 / (2*sigma^2))
    """
    exponent = numpy.exp(-((x - mean)**2) / (2 * std**2))
    coefficient = 1 / (numpy.sqrt(2 * numpy.pi) * std)
    return coefficient * exponent


# ============================================================================
# FUNCTION TO RUN NAIVE BAYES ON A DATASET
# ============================================================================

def run_naive_bayes(trainingFile, testingFile, dataset_name):
    """
    Run Naive Bayes classifier on a dataset and return results
    """
    print("\n" + "="*60)
    print("DATASET: " + dataset_name)
    print("="*60)
    
    # ========================================================================
    # TRAINING PHASE
    # ========================================================================
    
    # Load training data
    Xtrain = numpy.loadtxt(trainingFile)
    n = Xtrain.shape[0]  # Number of training samples
    d = Xtrain.shape[1] - 1  # Number of features (columns minus the label)
    print("Training samples:", n, "Features:", d)
    
    # Training... Collect mean and standard deviation for each dimension for each class..
    # Also, calculate P(C+) and P(C-)
    
    # Separate features and labels
    X_train_features = Xtrain[:, 0:d]  # All columns except last (features)
    y_train_labels = Xtrain[:, d]      # Last column (class labels: 1 or -1)
    
    # Separate data by class
    # C+ corresponds to class label = 1
    # C- corresponds to class label = -1
    X_class_positive = X_train_features[y_train_labels == 1]  # C+
    X_class_negative = X_train_features[y_train_labels == -1] # C-
    
    # Calculate prior probabilities
    # P(C+) = number of positive samples / total samples
    # P(C-) = number of negative samples / total samples
    n_positive = X_class_positive.shape[0]
    n_negative = X_class_negative.shape[0]
    P_C_positive = n_positive / n  # P(C+)
    P_C_negative = n_negative / n  # P(C-)
    
    # Calculate mean and standard deviation for each feature (dimension) for each class
    # For C+ (positive class)
    mean_positive = numpy.mean(X_class_positive, axis=0)  # Mean for each feature
    std_positive = numpy.std(X_class_positive, axis=0)    # Std for each feature
    
    # For C- (negative class)
    mean_negative = numpy.mean(X_class_negative, axis=0)  # Mean for each feature
    std_negative = numpy.std(X_class_negative, axis=0)    # Std for each feature
    
    # ========================================================================
    # TESTING PHASE
    # ========================================================================
    
    # Testing .....
    Xtest = numpy.loadtxt(testingFile)
    nn = Xtest.shape[0]  # Number of points in the testing data.
    print("Testing samples:", nn)
    
    tp = 0  # True Positive
    fp = 0  # False Positive
    tn = 0  # True Negative
    fn = 0  # False Negative
    
    # Iterate over all points in testing data
    for i in range(nn):
        # Get the i-th test sample (features only, not the label yet)
        Xi = Xtest[i, 0:d]
        
        # For each point find the P(C+|Xi) and P(C-|Xi) and decide if the point belongs to C+ or C-
        # Recall we need to calculate P(Xi|C+)*P(C+)
        # P(Xi|C+) = P(Xi1|C+) * P(Xi2|C+)....P(Xid|C+)....Do the same for P(Xi|C-)
        
        # Calculate P(Xi|C+) * P(C+)
        # Use log to avoid numerical underflow: log(A*B) = log(A) + log(B)
        log_prob_positive = numpy.log(P_C_positive)  # Start with log(P(C+))
        
        # Multiply probability for each feature (dimension)
        for j in range(d):
            # Calculate P(Xij|C+) using Gaussian distribution
            feature_prob = gaussian_probability(Xi[j], mean_positive[j], std_positive[j])
            log_prob_positive += numpy.log(feature_prob + 1e-10)  # Add small value to avoid log(0)
        
        # Calculate P(Xi|C-) * P(C-)
        log_prob_negative = numpy.log(P_C_negative)  # Start with log(P(C-))
        
        # Multiply probability for each feature (dimension)
        for j in range(d):
            # Calculate P(Xij|C-) using Gaussian distribution
            feature_prob = gaussian_probability(Xi[j], mean_negative[j], std_negative[j])
            log_prob_negative += numpy.log(feature_prob + 1e-10)
        
        # Now that you've calculated P(Xi|C+) and P(Xi|C-), we can decide which is higher
        # P(Xi|C+)*P(C+) or P(Xi|C-)*P(C-)
        if log_prob_positive > log_prob_negative:
            predicted_label = 1  # Predict C+ (positive class)
        else:
            predicted_label = -1  # Predict C- (negative class)
        
        # Get the true label for the i-th point
        # Remember the true label for the ith point is in Xtest[i, d]
        true_label = Xtest[i, d]
        
        # Increment TP, FP, FN, TN accordingly
        if predicted_label == 1 and true_label == 1:
            tp += 1  # True Positive: Predicted positive, actually positive
        elif predicted_label == 1 and true_label == -1:
            fp += 1  # False Positive: Predicted positive, actually negative
        elif predicted_label == -1 and true_label == -1:
            tn += 1  # True Negative: Predicted negative, actually negative
        elif predicted_label == -1 and true_label == 1:
            fn += 1  # False Negative: Predicted negative, actually positive
    
    # ========================================================================
    # CALCULATE ALL THE MEASURES REQUIRED
    # ========================================================================
    
    # Calculate all the measures required..
    print("\nRESULTS:")
    print("-" * 60)
    
    # Confusion Matrix
    print("\nConfusion Matrix:")
    print("                    PREDICTED")
    print("                 |  Positive | Negative |")
    print("    ACTUAL   ----+-----------+----------+")
    print("    Positive | TP = {:2d}   | FN = {:2d}   |".format(tp, fn))
    print("             +-----------+----------+")
    print("    Negative | FP = {:2d}   | TN = {:2d}   |".format(fp, tn))
    print("             +-----------+----------+")
    
    print("\nConfusion Matrix Values:")
    print("  True Positives (TP):  ", tp)
    print("  False Positives (FP): ", fp)
    print("  True Negatives (TN):  ", tn)
    print("  False Negatives (FN): ", fn)
    
    # Calculate Accuracy
    accuracy = (tp + tn) / (tp + fp + tn + fn)
    print("\nAccuracy: {:.4f} ({:.2f}%)".format(accuracy, accuracy * 100))
    
    # Calculate Precision
    if (tp + fp) > 0:
        precision = tp / (tp + fp)
    else:
        precision = 0
    print("Precision: {:.4f}".format(precision))
    
    # Calculate Recall
    if (tp + fn) > 0:
        recall = tp / (tp + fn)
    else:
        recall = 0
    print("Recall: {:.4f}".format(recall))
    
    # Calculate F-measure
    if (precision + recall) > 0:
        f_measure = 2 * (precision * recall) / (precision + recall)
    else:
        f_measure = 0
    print("F-measure: {:.4f}".format(f_measure))
    
    # Return results as a dictionary
    return {
        'tp': tp, 'fp': fp, 'tn': tn, 'fn': fn,
        'accuracy': accuracy, 'precision': precision,
        'recall': recall, 'f_measure': f_measure
    }


# ============================================================================
# MAIN PROGRAM - TEST ON BOTH DATASETS
# ============================================================================

print("="*60)
print("NAIVE BAYES CLASSIFIER")
print("="*60)
print("\nTesting on two datasets:")
print("  1. Iris (4 features)")
print("  2. Iris PC (2 features from PCA)")

# Dataset 1: Iris
results_iris = run_naive_bayes(
    "irisTraining.txt",
    "irisTesting.txt",
    "IRIS (4 features)"
)

# Dataset 2: Iris PC
results_pc = run_naive_bayes(
    "irisPCTraining.txt",
    "irisPCTesting.txt",
    "IRIS PC (2 features from PCA)"
)

# ============================================================================
# SUMMARY
# ============================================================================

print("\n" + "="*60)
print("SUMMARY")
print("="*60)

print("\nIris Dataset (4 features):")
print("  Accuracy: {:.4f} ({:.2f}%)".format(results_iris['accuracy'], results_iris['accuracy']*100))
print("  TP={}, FP={}, TN={}, FN={}".format(
    results_iris['tp'], results_iris['fp'], results_iris['tn'], results_iris['fn']))

print("\nIris PC Dataset (2 features):")
print("  Accuracy: {:.4f} ({:.2f}%)".format(results_pc['accuracy'], results_pc['accuracy']*100))
print("  TP={}, FP={}, TN={}, FN={}".format(
    results_pc['tp'], results_pc['fp'], results_pc['tn'], results_pc['fn']))

print("\n" + "="*60)
print("PROGRAM COMPLETED SUCCESSFULLY")
print("="*60)
