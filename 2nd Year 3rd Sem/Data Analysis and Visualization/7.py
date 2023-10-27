import pandas as pd

# Create the data frame
data = {'Name': ['Shah', 'Vats', 'Vats', 'Kumar', 'Vats', 'Kumar', 'Shah', 'Shah', 'Kumar', 'Vats'],
        'Gender': ['Male', 'Male', 'Female', 'Male', 'Female', 'Male', 'Male', 'Female', 'Female', 'Male'],
        'MonthlyIncome (Rs.)': [114000.00, 65000.00, 43150.00, 69500.00, 155000.00, 103000.00, 55000.00, 112400.00, 81030.00, 71900.00]}
df = pd.DataFrame(data)

gross_income = df.groupby('Name')['MonthlyIncome (Rs.)'].sum()
print('\nFamily wise gross income:-')
print(gross_income)

max_income = df['MonthlyIncome (Rs.)'].max()
print('Maximum Income: {}'.format(max_income))

income_gt_60k = df.loc[df['MonthlyIncome (Rs.)']  > 60000]
print('\nMembers having income greater than 60k: ')
print(income_gt_60k)

avg_income_female = df.groupby('Gender')['MonthlyIncome (Rs.)'].mean()
print('\nAverage income for female: {}'.format(avg_income_female['Female']))
