## General
WORKSPACE = "D:\Workspace\Dataanalysis_homework_5\Regression"
DATA_PATH = WORKSPACE + "\\2024-introduction-to-data-analysis-hw-5-2"
LOG_PATH = WORKSPACE
LOG = True # True, False
LOG_FILE = LOG_PATH + "\\log.txt"

## Data preprocessing
METHOD_PROCESSING_MISSING_VALUES = "med"
NUM_SELECTED_FEATURES = 14 # max: 19
ADD_TSNE = (False, 3)
ADD_PCA = (False, 3)
SCALER = "std"

## Model select
METHOD_VALIDATION = "skf"
NUM_FOLDS = 5
METHOD_MODEL = "rf"
METHOD_SEARCH = "random"

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
    'C': [0.1, 1, 5, 10, 15, 20, 50, 100],
    'gamma': ["auto", 1, 0.7, 0.5, 0.3, 0.1, 0.05, 0.01],
    'kernel': ['rbf', 'linear', 'poly', 'sigmoid']
}
# Note: https://scikit-learn.org/dev/modules/generated/sklearn.svm.SVC.html

## Random Forest
RANDOM_FOREST_PARAMS = {
    'bootstrap': [True, False],
    'max_depth': [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, None],
    'max_features': [None, 'sqrt', 2],
    'min_samples_leaf': [1, 2, 4],
    'min_samples_split': [2, 5, 10],
    'n_estimators': [200, 400, 600, 800, 1000, 1200, 1400],
    # 'criterion' :['mse'],
}


