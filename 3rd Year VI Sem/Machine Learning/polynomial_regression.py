import numpy as np
import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Load the California Housing dataset
housing = fetch_california_housing()
X = housing.data
y = housing.target

# Split the dataset into training and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Transform the features to polynomial features
poly = PolynomialFeatures(degree=2)
X_poly = poly.fit_transform(X_train)

# Create a Polynomial Regression model
model = LinearRegression()
model.fit(X_poly, y_train)

# Predict the test set results
X_test_poly = poly.transform(X_test)
y_pred = model.predict(X_test_poly)

# Evaluate the model
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print(f"Mean Squared Error: {mse}")
print(f"R² Score: {r2}")

# Perform k-cross-validation
cv_scores = cross_val_score(model, poly.fit_transform(X), y, cv=10, scoring='neg_mean_squared_error')
print(f"Cross-Validation MSE Scores: {-cv_scores}")
print(f"Mean CV MSE Score: {-np.mean(cv_scores)}")
