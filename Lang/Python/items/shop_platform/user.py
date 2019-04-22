import time

def user_get_name(user_info):
	user_item = user_info.split(',')
	return user_item[0]

def user_get_pwd(user_info):
	user_item = user_info.split(',')
	return user_item[1]
	
def user_get_activeflag(user_info):
	user_item = user_info.split(',')
	return user_item[3]

def get_user_info(all_user_info,name):
	for user_info in all_user_info:
		if name == user_get_name(user_info):
			return user_info
	return False
	
def user_exit(all_user_info,name):
	for user_info in all_user_info:
		if name == user_get_name(user_info):
			return True
	return False

def set_user_info(name,pwd,active='1'):
	info = name + ',' + pwd + ','
	info += time.strftime('%Y-%m-%d %H:%M:%S') + ','
	info += active
	info += '\n'
	return info


def register():
	while True:
		print('--------------- register ----------------')
		user_name = input('Please input the user name(len >= 3)[q -> quit]:\n')
		if user_name == 'q':
			break
		if len(user_name) < 3:
			continue
		f_user = open('user.csv','a+')
		f_user.seek(0)
		f_lines = f_user.readlines()
		if not user_exit(f_lines,user_name):
			user_pwd = input('Please input the password(len >= 6): ')
			while True:
				if len(user_pwd) < 6:
					user_pwd = input('Please input the password(len >= 6): ')
					continue
				user_pwd2 = input('Please input the password again: ')
				if user_pwd == user_pwd2:
					break
				else:
					print('Two inconsistent passwords')
					user_pwd = input('Please input the password(len >= 6): ')
			user_info = set_user_info(user_name,user_pwd)
			f_user.write(user_info)
		else:
			print('user exist! ')
		f_user.close()

def login():
	while True:
		print('--------------- register ----------------')
		user_name = input('Please input the user name(len >= 3)[q -> quit]:\n')
		if user_name == 'q':
			break
		if len(user_name) < 3:
			continue
		f_user = open('user.csv','r+')
		f_user.seek(0)
		f_lines = f_user.readlines()
		f_user.close()
		
		if user_exit(f_lines,user_name):
			user_info = get_user_info(f_lines,user_name)
			if user_get_activeflag(user_info) == '0':
				print('user account is locked!')
				continue
			user_pwd0 = user_get_pwd(user_info)
			count = 3
			user_pwd = input('Please input the password(len >= 6)')
			while count > 0:
				if len(user_pwd) < 6:
					user_pwd = input('Please input the password(len >= 6): ')
					continue
				if user_pwd != user_pwd0:
					print('Password is Error! left_count = {}'.format(count))
					user_pwd = input('Please input the password(len >= 6): ')
					count -= 1
					continue
				else:
					break
			
			if count != 0:
				print('Login Success !')
				break
			else:
				print('user account is locked!')
				index = f_lines.index(user_info)
				pre_user_info = set_user_info(user_name,user_pwd,active='0')
				f_lines[index] = pre_user_info
				f_user.wirtelines(f_lines)
				break
		else:
			print('user not exist! ')

login()
