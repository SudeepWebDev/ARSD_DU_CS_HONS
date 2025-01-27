# Machine Learning Practicals

This repository contains various machine learning practicals using different datasets and algorithms. Below is a summary of each script, the dataset used, and the tasks performed.

## Datasets

1. **California Housing Dataset**: Used for regression tasks.
   - Source: [California Housing Dataset](https://scikit-learn.org/stable/modules/generated/sklearn.datasets.fetch_california_housing.html)
2. **Iris Dataset**: Used for classification tasks.
   - Source: [Iris Dataset](https://scikit-learn.org/stable/modules/generated/sklearn.datasets.load_iris.html)

## Scripts

### 1. Simple Linear Regression
- **File**: `boston_regression.py`
- **Dataset**: California Housing Dataset
- **Tasks**: Train a simple linear regression model, evaluate using MSE and R² score, perform k-cross-validation.

### 2. Multiple Linear Regression
- **File**: `multiple_linear_regression.py`
- **Dataset**: California Housing Dataset
- **Tasks**: Train a multiple linear regression model, evaluate using MSE and R² score, perform k-cross-validation.

### 3. Polynomial Regression
- **File**: `polynomial_regression.py`
- **Dataset**: California Housing Dataset
- **Tasks**: Train a polynomial regression model, evaluate using MSE and R² score, perform k-cross-validation.

### 4. Lasso and Ridge Regression
- **File**: `lasso_ridge_regression.py`
- **Dataset**: California Housing Dataset
- **Tasks**: Train Lasso and Ridge regression models, evaluate using MSE and R² score, perform k-cross-validation.

### 5. Logistic Regression
- **File**: `logistic_regression.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train a logistic regression model, evaluate using accuracy, confusion matrix, classification report, ROC AUC score, perform k-cross-validation.

### 6. Artificial Neural Network (ANN) Classifier
- **File**: `ann_classifier.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train an ANN classifier, evaluate using accuracy, confusion matrix, classification report, ROC AUC score, perform k-cross-validation.

### 7. K-NN Classifier
- **File**: `knn_classifier.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train a K-NN classifier, evaluate using accuracy, confusion matrix, classification report, ROC AUC score, perform k-cross-validation.

### 8. Decision Tree Classifier
- **File**: `decision_tree_classifier.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train a decision tree classifier, evaluate using accuracy, confusion matrix, classification report, ROC AUC score, perform k-cross-validation.

### 9. SVM Classifier
- **File**: `svm_classifier.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train an SVM classifier, evaluate using accuracy, confusion matrix, classification report, ROC AUC score, perform k-cross-validation.

### 10. Naïve Bayes Classifier
- **File**: `iris_classification.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train a Naïve Bayes classifier, evaluate using accuracy, confusion matrix, classification report, ROC AUC score, perform k-cross-validation.

### 11. K-means Clustering
- **File**: `kmeans_clustering.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train a K-means clustering model, evaluate using silhouette score.

### 12. Hierarchical Clustering
- **File**: `hierarchical_clustering.py`
- **Dataset**: Iris Dataset
- **Tasks**: Train a hierarchical clustering model, evaluate using silhouette score.

## How to Run

1. Ensure you have Python installed.
2. Install the required libraries using:
   ```sh
   pip install numpy pandas scikit-learn
   ```
3. Run each script using:
   ```sh
   python <script_name>.py
   ```

## Notes

- The California Housing dataset is used for regression tasks due to its continuous target variable.
- The Iris dataset is used for classification tasks due to its categorical target variable.
- Each script includes model training, evaluation, and cross-validation where applicable.