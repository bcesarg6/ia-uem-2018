# Percepton implementation for poker hand
# Authors: Bruno Cesar, Cristofer Oswald and Narcizo Gabriel
# Date: 25/11/2018

from csv import reader
from src.Perceptron import Perceptron

train_file = 'train_min.data'
test_file = 'test.data'

learning_rate = 0.1
n_epochs = 5


def main():
    perceptrons = []
    new_data = []

    print("Starting run...")
    print("\tTrain file: " + train_file)
    print("\tTest file: " + test_file + "\n")

    trainset = read_file(train_file)
    print("Trainset ready.")

    testset = read_file(test_file)
    print("Testset ready.")

    for i in range(10):
        new_data.append(setup_dataset(trainset, i))
    trainset = new_data

    new_data = []
    for i in range(10):
        new_data.append(setup_dataset(testset, i))
    testset = new_data

    for i in range(10):
        perceptrons.append(Perceptron(trainset, testset, learning_rate, n_epochs))
        print(perceptrons[i])

    for perceptron in perceptrons:
        perceptron.train()
        perceptron.test()


def read_file(file_name):
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
    new_dataset = []

    for data in dataset:
        for row in data:
            new_row = row.copy()
            new_row[-1] = 1 if new_row[-1] == ind else 0
            new_dataset.append(new_row)

    return new_dataset


if __name__ == "__main__":
    main()
