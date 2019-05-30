def read_file(filename, size):
	f = open(filename, 'r')
	nums = []
	for i in range(size):
		nums.append([])

	for line in f:
		r = 0
		T = ""

		while line[r] != ' ':
			T += line[r]
			r += 1

		for i in range(size):
			while line[r] == ' ':
				r += 1
			Q = ""
			while line[r] != ' ' and line[r] != '\n':
				Q += line[r]
				r += 1
			num = [float(T), float(Q)]
			nums[i].append(num)
	f.close()

	return nums


def interpolate_coeff(filename, size):
	Q_T = read_file(filename, size)
	for i in range(size):
		n = len(Q_T[i])
		for k in range(n):
			for l in range(n - 1):
				Q_T[i][k].append(0)

	for k in range(size):
		n = len(Q_T[k])
		for i in range(n - 1):
			for l in range(i + 1, n, 1):
				Q_T[k][l][i + 2] = (Q_T[k][l - 1][i + 2 - 1] - Q_T[k][l][i + 2 - 1]) /\
								(Q_T[k][l - i - 1][0] - Q_T[k][l][0])

	return Q_T


def interpolate(filename, T, size):
	Q_T = interpolate_coeff(filename, size)

	res = []
	for i in range(size):
		res.append(Q_T[i][0][1])
		n = len(Q_T[i])
		for k in range(n - 1):
			get_mult = 1
			for j in range(k + 1):
				get_mult *= T - Q_T[i][j][0]
			get_mult *= Q_T[i][j + 1][j + 2]
			res[i] += get_mult

	return res
