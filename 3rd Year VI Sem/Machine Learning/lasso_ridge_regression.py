import numpy as np
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.linear_model import Lasso, Ridge
from sklearn.metrics import mean_squared_error, r2_score

# Load the California Housing dataset
housing = fetch_california_housing()
X = housing.data
y = housing.target

# Split the dataset into training and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Create and evaluate Lasso Regression model
lasso = Lasso()
lasso.fit(X_train, y_train)
y_pred_lasso = lasso.predict(X_test)
mse_lasso = mean_squared_error(y_test, y_pred_lasso)
r2_lasso = r2_score(y_test, y_pred_lasso)
print(f"Lasso Regression - Mean Squared Error: {mse_lasso}")
print(f"Lasso Regression - R² Score: {r2_lasso}")

# Perform k-cross-validation for Lasso
cv_scores_lasso = cross_val_score(lasso, X, y, cv=10, scoring='neg_mean_squared_error')
print(f"Lasso Regression - Cross-Validation MSE Scores: {-cv_scores_lasso}")
print(f"Lasso Regression - Mean CV MSE Score: {-np.mean(cv_scores_lasso)}")

# Create and evaluate Ridge Regression model
ridge = Ridge()
ridge.fit(X_train, y_train)
y_pred_ridge = ridge.predict(X_test)
mse_ridge = mean_squared_error(y_test, y_pred_ridge)
r2_ridge = r2_score(y_test, y_pred_ridge)
print(f"Ridge Regression - Mean Squared Error: {mse_ridge}")
print(f"Ridge Regression - R² Score: {r2_ridge}")

# Perform k-cross-validation for Ridge
cv_scores_ridge = cross_val_score(ridge, X, y, cv=10, scoring='neg_mean_squared_error')
print(f"Ridge Regression - Cross-Validation MSE Scores: {-cv_scores_ridge}")
print(f"Ridge Regression - Mean CV MSE Score: {-np.mean(cv_scores_ridge)}")
