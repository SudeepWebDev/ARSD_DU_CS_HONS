import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Load the California Housing dataset

housing = pd.read_csv('3rd Year VI Sem/Machine Learning/lrdata.csv')  # Ensure this file is in the same folder
print(housing.head())
X = housing[['area']]  
y = housing[['price']]

# Split the dataset into training and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Create a Simple Linear Regression model
model = LinearRegression()
model.fit(X_train, y_train)

# Predict the test set results
y_pred = model.predict(X_test)

# Evaluate the model
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print(f"Mean Squared Error: {mse}")
print(f"R² Score: {r2}")

# Perform k-cross-validation
cv_scores = cross_val_score(model, X, y, cv=3, scoring='neg_mean_squared_error')
print(f"Mean CV MSE Score: {-np.mean(cv_scores)}")

# Manual calculation of b0 and b1
mean_x = np.mean(X_train['area'])
mean_y = np.mean(y_train)

b1_num = 0
b1_den = 0
for i in range(len(X_train)):
    b1_num += (X_train.iloc[i, 0] - mean_x) * (y_train.iloc[i] - mean_y)
    b1_den += (X_train.iloc[i, 0] - mean_x) ** 2
b1_manual = b1_num / b1_den
b0_manual = mean_y - b1_manual * mean_x

print(f"Manual b0: {b0_manual}, b1: {b1_manual}")

pred_5000_manual = b0_manual + b1_manual * 5000
pred_6000_manual = b0_manual + b1_manual * 6000
print(f"Manual prediction for area=5000: {pred_5000_manual}")
print(f"Manual prediction for area=6000: {pred_6000_manual}")

# Predict for specific area values
pred_5000 = model.predict([[5000]])
pred_6000 = model.predict([[6000]])
print(f"Prediction for area=5000: {pred_5000[0]}")
print(f"Prediction for area=6000: {pred_6000[0]}")

# Plot the regression line
import matplotlib.pyplot as plt
plt.scatter(X_test, y_test, color='blue', label='Actual data')
plt.plot(X_test, y_pred, color='red', linewidth=2, label='Regression line')
plt.xlabel('Area')
plt.ylabel('Price')
plt.title('Linear Regression Fit')
plt.legend()
plt.show()
plt.savefig("plot.png")