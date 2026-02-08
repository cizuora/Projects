============================================================
NAIVE BAYES CLASSIFIER
============================================================

Testing on two datasets:
  1. Iris (4 features)
  2. Iris PC (2 features from PCA)

============================================================
DATASET: IRIS (4 features)
============================================================
Training samples: 100 Features: 4
Testing samples: 50

RESULTS:
------------------------------------------------------------

Confusion Matrix:
                    PREDICTED
                 |  Positive | Negative |
    ACTUAL   ----+-----------+----------+
    Positive | TP = 16   | FN =  0   |
             +-----------+----------+
    Negative | FP =  1   | TN = 33   |
             +-----------+----------+

Confusion Matrix Values:
  True Positives (TP):   16
  False Positives (FP):  1
  True Negatives (TN):   33
  False Negatives (FN):  0

Accuracy: 0.9800 (98.00%)
Precision: 0.9412
Recall: 1.0000
F-measure: 0.9697

============================================================
DATASET: IRIS PC (2 features from PCA)
============================================================
Training samples: 100 Features: 2
Testing samples: 50

RESULTS:
------------------------------------------------------------

Confusion Matrix:
                    PREDICTED
                 |  Positive | Negative |
    ACTUAL   ----+-----------+----------+
    Positive | TP = 15   | FN =  1   |
             +-----------+----------+
    Negative | FP =  4   | TN = 30   |
             +-----------+----------+

Confusion Matrix Values:
  True Positives (TP):   15
  False Positives (FP):  4
  True Negatives (TN):   30
  False Negatives (FN):  1

Accuracy: 0.9000 (90.00%)
Precision: 0.7895
Recall: 0.9375
F-measure: 0.8571

============================================================
SUMMARY
============================================================

Iris Dataset (4 features):
  Accuracy: 0.9800 (98.00%)
  TP=16, FP=1, TN=33, FN=0

Iris PC Dataset (2 features):
  Accuracy: 0.9000 (90.00%)
  TP=15, FP=4, TN=30, FN=1

============================================================
PROGRAM COMPLETED SUCCESSFULLY
============================================================