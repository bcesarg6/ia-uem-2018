# Percepton implementation for poker hand
# Authors: Bruno Cesar, Cristofer Oswald and Narcizo Gabriel
# Date: 25/11/2018

from csv import reader
from src.Perceptron import Perceptron

train_file = 'test.data'
test_file = 'train.data'

learning_rate = 0.001
n_epochs = 1000


def main():
    perceptrons = []
    new_data = []

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

    print(test_all(perceptrons, test_data))

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


def setup_test(testset):
    """
    Creates a array with the problem class of each instance
    :param testset: The full testset
    :return: The array
    """
    new_testset = []

    for claz in testset:
        for instance in claz:
            new_testset.append(instance[-1])

    return new_testset


def test_all(perceptrons, test_data):
    """
    Run the tests using all perceptrons as one unit and return the results
    :param perceptrons: The perceprons list
    :param test_data: The array containing the right answer
    :return: The confusion matrix
    """
    result = []

    for i in range(11):
        result.append([])
        for j in range(11):
            result[i].append(0)

    print("Testing perceptrons...")

    for i in range(len(test_data)):
        res = 0
        for j in range(len(perceptrons)):
            res = perceptrons[j].test(i)
            if res:
                res = j
                break

        if not res:
            res = 10

        result[test_data[i]][res] = result[test_data[i]][res] + 1

    print("Testing all done\n")

    return result


if __name__ == "__main__":
    main()
