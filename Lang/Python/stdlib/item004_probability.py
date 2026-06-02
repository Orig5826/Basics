
import random

def win_probablity(P):
    return random.random() < P/100

def test_probablity(P, count=10000):
    win_cnt = 0
    for i in range(count):
        if win_probablity(P):
            win_cnt+=1
    actual = win_cnt/count*100
    print("{:7}: expect={:7.2f}%, actual={:7.2f}%, err_rate={:7.2f}%".format(count, P, actual, (actual/P-1)*100))

def test_probablity_with_error(P, error=0.01):
    count = int((1/error)**2)
    test_probablity(P, count)


def test_with_count(count):
    print(" -------------------- {} -------------------- ".format(count))
    for i in range(10):
        test_probablity(50, count)

def test_with_error(error):
    print(" -------------------- {:6.2f}% -------------------- ".format(error*100))
    for i in range(10):
        test_probablity_with_error(50, error)


def test():
    # test_with_count(100)
    # test_with_count(1000)
    # test_with_count(1000)
    # test_with_count(10000)
    # test_with_count(100000)

    test_with_error(1)
    test_with_error(0.5)
    test_with_error(0.01)
    test_with_error(0.005)
    test_with_error(0.001)
    
if __name__ == "__main__":
    test()
