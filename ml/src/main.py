# Percepton implementation for poker hand
# Authors: Bruno Cesar, Cristofer Oswald and Narcizo Gabriel
# Date: 25/11/2018
import math
import random
from csv import reader

train_file = 'test.data'
test_file = 'train.data'
mushroom_file = "mushroom.data"

learning_rate = 0.01
n_epochs = 100

is_sig = False
mushroom = True

if is_sig:
    from src.PerceptronSig import PerceptronSig as Perceptron
else:
    from src.Perceptron import Perceptron as Perceptron


def main():
    print("Run: " + str(learning_rate) + ", " + str(n_epochs) + ", sigmoid: " + str(is_sig))
    perceptrons = []
    new_data = []
    test_data = []

    if mushroom:
        print("Starting run...")
        print("Input file: " + mushroom_file)

        data = read_mushroom(mushroom_file)
        train_set = data[:math.floor(int(len(data)*0.8))]
        testset = data[math.floor(int(len(data)*0.8)):]

        perceptrons.append(Perceptron(train_set, testset, learning_rate, n_epochs))

        test_data = setup_test(testset, mush=True)
    else:
        print("Starting run...")
        print("\tTrain file: " + train_file)
        print("\tTest file: " + test_file + "\n")

        trainset = read_file(train_file)

        for i in range(10):
            new_data.append(setup_dataset(trainset, i))
        trainset = new_data
        print("Trainset ready.\n")

        testset = read_file(test_file)
        test_data = setup_test(testset)

        new_data = []
        for i in range(10):
            new_data.append(setup_dataset(testset, i))
        testset = new_data
        print("Testset ready.\n")

        print("Setting up perceptrons...")
        for i in range(10):
            perceptrons.append(Perceptron(trainset[i], testset[i], learning_rate, n_epochs))
        print("Perceptrons ready to be trained\n")

    print("Starting training...")
    for i in range(len(perceptrons)):
        print("Training perceptron " + str(i))
        perceptrons[i].train()
        print("Done.")
    print("Training all done\n")

    if is_sig:
        confusion_matrix = test_all_sig(perceptrons, test_data)
    else:
        confusion_matrix = test_all_lim(perceptrons, test_data)

    print(confusion_matrix)
    print()
    print(read_confusion_matrix(confusion_matrix))
    print("End.")


def read_file(file_name):
    """
    Creates a list of matrixes, in order that each matrix has only the instance class (0 - 9) of its position
    :param file_name: The file to be read
    :return: The list of matrixes
    """
    dataset = [[], [], [], [], [], [], [], [], [], []]

    print("Reading file: " + file_name)

    with open(file_name, 'r') as file:
        csv_data = reader(file)

        for row_data in csv_data:
            if not row_data:
                continue

            data = []
            for val in row_data:
                data.append(int(val))

            dataset[data[-1]].append(data)

    return dataset


def read_mushroom(file_name):
    print("Reading file: " + file_name)

    data = []
    data_set = []
    for _ in range(23):
        data.append(dict())
    with open(file_name, 'r') as file:
        lines = file.readlines()
        for line in lines:
            d = line.split(',')

            for char in range(len(d)):
                if char == 0:
                    continue

                if data[char - 1].get(d[char]) is None:
                    data[char-1].update({d[char]: len(data[char-1])})

            if data[-1].get(d[0]) is None:
                if len(data[-1]) < 1:
                    data[-1].update({d[0]: 0})
                else:
                    data[-1].update({d[0]: len(data[-1])})

        i = 0
        for line in lines:
            data_set.append([])
            chars = line.split(',')

            for char in range(len(chars)):
                if char == 0:
                    continue

                data_set[i].append(data[char-1].get(chars[char]))

            data_set[i].append((data[-1].get(chars[0])))
            i = i + 1

    return data_set


def setup_dataset(dataset, ind):
    """
    Normalizes dataset, creating copies for each problem class
    :param dataset: Dataset to be normalized
    :param ind: The class index
    :return: The new dataset
    """
    new_dataset = []

    for data in dataset:
        for row in data:
            new_row = row.copy()
            new_row[-1] = 1 if new_row[-1] == ind else 0
            new_dataset.append(new_row)

    return new_dataset


def setup_test(testset, mush=False):
    """
    Creates a array with the problem class of each instance
    :param testset: The full testset
    :return: The array
    """
    new_testset = []

    if not mush:
        for claz in testset:
            for instance in claz:
                new_testset.append(instance[-1])
    else:
        for instance in testset:
            new_testset.append(instance[-1])

    return new_testset


def test_all_lim(perceptrons, test_data):
    """
    Run the tests using all perceptrons as one unit and return the results
    :param perceptrons: The perceprons list
    :param test_data: The array containing the right answer
    :return: The confusion matrix
    """
    confusion_matrix = []

    for i in range(2):
        confusion_matrix.append([])
        for j in range(2):
            confusion_matrix[i].append(0)

    print("Testing limiar perceptrons...")

    for i in range(len(test_data)):
        res = 0
        if len(perceptrons) > 1:
            for j in range(len(perceptrons)):
                res = perceptrons[j].test(i)
                if res:
                    res = j
                    break

            if not res:
                res = 10

            confusion_matrix[test_data[i]][res] = confusion_matrix[test_data[i]][res] + 1
        else:
            res = perceptrons[-1].test(i)
            confusion_matrix[test_data[i]][res] = confusion_matrix[test_data[i]][res] + 1

    print("Testing all done\n")

    return confusion_matrix


def test_all_sig(perceptrons, test_data):
    """
        Run the tests using all perceptrons as one unit and return the results
        :param perceptrons: The perceprons list
        :param test_data: The array containing the right answer
        :return: The confusion matrix
        """
    confusion_matrix = []

    for i in range(2):
        confusion_matrix.append([])
        for j in range(2):
            confusion_matrix[i].append(0)

    print("Testing sigmoid perceptrons...")

    for i in range(len(test_data)):
        result = []
        if len(perceptrons) > 1:
            for j in range(len(perceptrons)):
                result.append([perceptrons[j].test(i), j])

            result.sort(key=take_first, reverse=True)

            confusion_matrix[test_data[i]][result[0][1]] = confusion_matrix[test_data[i]][result[0][1]] + 1

        else:
            result = perceptrons[-1].test(i)

            result = 0 if result > 0.5 else 1

            confusion_matrix[test_data[i]][result] = confusion_matrix[test_data[i]][result] + 1

    print("Testing all done\n")

    return confusion_matrix


def read_confusion_matrix(matrix):
    total = [0.0]*len(matrix)
    total_tp = [0.0]*len(matrix)
    total_fp = [0.0]*len(matrix)
    total_fn = [0.0]*len(matrix)

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            total[i] = total[i] + matrix[i][j]

            if i == j:
                total_tp[i] = matrix[i][j]
            else:
                total_fp[j] = total_fp[j] + matrix[i][j]
                total_fn[i] = total_fn[i] + matrix[i][j]

    total_examples = 0.0
    accuracy = 0.0
    precision = []
    recall = []
    f1 = []

    for i in range(len(total)):
        accuracy = accuracy + total_tp[i]
        total_examples = total_examples + total[i]
        if total_tp[i] > 0:
            precision.append(100*(total_tp[i]/(total_tp[i]+total_fp[i])))
            recall.append(100*(total_tp[i]/(total_tp[i]+total_fn[i])))
            f1.append((2*((precision[i]*recall[i])/(precision[i]+recall[i]))))
        else:
            precision.append(0.0)
            recall.append(0.0)
            f1.append(0.0)

    accuracy = accuracy/total_examples

    return [100*accuracy, precision, recall, f1]


def take_first(elem):
    return elem[0]


if __name__ == "__main__":
    main()
