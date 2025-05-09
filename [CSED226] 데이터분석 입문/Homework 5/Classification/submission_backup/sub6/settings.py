## General
WORKSPACE = "D:\Workspace\Dataanalysis_homework_5\Classification"
DATA_PATH = WORKSPACE + "\\2024-introduction-to-data-analysis-hw-5-1"
LOG_PATH = WORKSPACE + "\\log"
LOG = True # True, False
LOG_FILE = LOG_PATH + "\\log.txt"

## Data preprocessing
METHOD_PROCESSING_MISSING_VALUES = "drop"
NUM_SELECTED_FEATURES = 14 # max: 19
ADD_TSNE = (False, 0)
ADD_PCA = (False, 0)
SCALER = "std"

## Model select
METHOD_VALIDATION = "skf"
NUM_FOLDS = 5
METHOD_MODEL = "svc"
# xgb, svc, rf

## XGBoost
XGBOOST_PARAMS = {
    'min_child_weight': [1, 5, 10],
    'gamma': [0.5, 1, 1.5, 2, 5],
    'subsample': [0.6, 0.8, 1.0],
    'colsample_bytree': [0.6, 0.8, 1.0],
    'max_depth': [3, 4, 5]
}
# Note: https://www.kaggle.com/code/tilii7/hyperparameter-grid-search-with-xgboost

## SVC
SVC_PARAMS = {
    'C': [0.1, 1, 5, 10, 15, 20],
    'gamma': ["auto", 1, 0.7, 0.5, 0.3, 0.1, 0.05, 0.01],
    'kernel': ['rbf']
}
# Note: https://scikit-learn.org/dev/modules/generated/sklearn.svm.SVC.html



