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

testX = ['>50', 'Medium', 'No', 'Excellent']

#print(Y)
s = set()
for elem in Y:
	s.add(elem)

c_values = list(s)

def prob_class(Y, c_val):
	s = len(Y)
	count = 0
	for elem in Y:
		if elem == c_val:
			count += 1

	return count, count / s

def unique_attributes(X, Y, col_no):
	s = set()
	for elem in X:
		s.add(elem[col_no])
	return len(s)		

def prob_attribute(X, Y, a_n, a_val, c_val, n_class):
	count = 0
	for row in zip(X, Y):
		X_row = row[0]
		Y_row = row[1]
		# print(X_row, Y_row)
		if X_row[a_n] == a_val and Y_row == c_val :
			count += 1
	#print(count, a_n, a_val, c_val, n_class)
	unique_values = unique_attributes(X, Y, a_n)
	return (count +  1) / (n_class + unique_values)


def bayesian(X, Y, testX):
	predicted_class = 'unknown'
	max_prob = -1
	n_attribute = len(X[0])
	for elem in c_values:
		#print(elem)
		n_count, prob = prob_class(Y, elem)
		#print(n_count, prob)
		for i in range(n_attribute):
			prob *= prob_attribute(X, Y, i, testX[i], elem, n_count) 
		print(prob,' ',elem)
		if prob >= max_prob:
			max_prob = prob
			predicted_class = elem
	return predicted_class

print(bayesian(X, Y, testX))