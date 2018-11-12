import xlrd
file = xlrd.open_workbook('DATASET3.xls')
task2 = file.sheet_by_index(0)
write_file = open('test_data.txt', 'w')

X = []
Y = []
for i in range(1, task2.nrows):
    a = task2.row_values(i)
    a = [i.strip() for i in a]
    X.append(a[1:-1])
    Y.append(a[-1])
    # print(a)

# print(X)
# print(Y)

# testX = ['T', 'T', 'F', 'T', 'Some', '$$$', 'T', 'T', 'Italian', '>60']
testX = ['<=30', 'High', 'No', 'Fair']

# c_val1 = 'T'
# c_val2 = 'F'
c_val1 = 'Yes'
c_val2 = 'No'
def prob_class(Y, c_val):
	s = len(Y)
	count = 0
	for elem in Y:
		if elem == c_val:
			count += 1

	return count, count / s

def prob_attribute(X, Y, a_n, a_val, c_val, n_class):
	count = 0
	for row in zip(X, Y):
		X_row = row[0]
		Y_row = row[1]
		# print(X_row, Y_row)
		if X_row[a_n] == a_val and Y_row == c_val :
			count += 1
	print(count, a_n, a_val, c_val, n_class)
	if count == 0:
		return 1/(n_class+1)
	return count / n_class


def bayesian(X, Y, testX):
	n_1, p_c1 = prob_class(Y, c_val1)
	n_2, p_c2 = prob_class(Y, c_val2)
	print(p_c1)
	print(p_c2)
	n_attribute = len(X[0])
	# prob_1 = [1] * n_attribute
	# prob_2 = [1] * n_attribute
	probability_1 = p_c1
	probability_2 = p_c2
	for i in range(n_attribute):
		probability_1 *= prob_attribute(X, Y, i, testX[i], c_val1, n_1)
		probability_2 *= prob_attribute(X, Y, i, testX[i], c_val2, n_2)
	
	print(probability_1)
	print(probability_2)	
	if probability_1 > probability_2:
		return 1
	else:
		return 2

print(bayesian(X, Y, testX))