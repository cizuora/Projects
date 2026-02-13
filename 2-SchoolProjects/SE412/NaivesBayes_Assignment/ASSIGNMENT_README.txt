
RESULTS:
------------------------------------------------------------
============================================================
DATASET: IRIS PC (4 features from PCA)
============================================================
Confusion Matrix:
                     PREDICTED
                 +------------+------------+
                 |  Positive  |  Negative  |
       ----------+------------+------------+
 ACTUAL Positive | TP =  16    | FN =   0    |
                 +------------+------------+
        Negative | FP =   1    | TN =  33    |
                 +------------+------------+

Detailed Statistics:
  True Positives (TP):  16
  False Positives (FP): 1
  True Negatives (TN):  33
  False Negatives (FN): 0

Performance Metrics:
  Accuracy:  0.9800 (98.00%)
  Precision: 0.9412
  Recall:    1.0000
  F1-Score:  0.9697

Processing IRIS PC (2 features from PCA)...

============================================================
DATASET: IRIS PC (2 features from PCA)
============================================================
Training samples loaded successfully
Testing samples loaded successfully

RESULTS:
------------------------------------------------------------

Confusion Matrix:
                     PREDICTED
                 +------------+------------+
                 |  Positive  |  Negative  |
       ----------+------------+------------+
 ACTUAL Positive | TP =  15    | FN =   1    |
                 +------------+------------+
        Negative | FP =   4    | TN =  30    |
                 +------------+------------+

Detailed Statistics:
  True Positives (TP):  15
  False Positives (FP): 4
  True Negatives (TN):  30
  False Negatives (FN): 1

Performance Metrics:
  Accuracy:  0.9000 (90.00%)
  Precision: 0.7895
  Recall:    0.9375
  F1-Score:  0.8571

============================================================
SUMMARY OF RESULTS
============================================================

IRIS (4 features):
  Accuracy:  0.9800 (98.00%)
  Precision: 0.9412
  Recall:    1.0000
  F1-Score:  0.9697
  TP=16, FP=1, TN=33, FN=0

IRIS PC (2 features from PCA):
  Accuracy:  0.9000 (90.00%)
  Precision: 0.7895
  Recall:    0.9375
  F1-Score:  0.8571
  TP=15, FP=4, TN=30, FN=1

============================================================
PROGRAM COMPLETED SUCCESSFULLY
============================================================