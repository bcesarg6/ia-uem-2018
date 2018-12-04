import math
import random


def sigmoid(val):
    return 1/(1 + math.exp(val*-1))


class PerceptronSig:
    def __init__(self, trainset, testset, learning_rate, n_epochs):
        self.trainset = trainset
        self.testset = testset
        self.learning_rate = learning_rate
        self.n_epochs = n_epochs
        self.weights = [0.0]*len(trainset[0])
        self.sig_z = sigmoid(0)

    def predict(self, train_line):
        activate = self.weights[0]

        for i in range(len(train_line) - 1):
            activate = activate + self.weights[i + 1]*train_line[i]

        return sigmoid(activate)

    def train(self):
        for epoch in range(self.n_epochs):
            random.shuffle(self.trainset)
            for train_line in self.trainset:
                predicted = self.predict(train_line)

                if train_line[-1] == 0:
                    if predicted < self.sig_z:
                        continue
                else:
                    if predicted >= self.sig_z:
                        continue

                error = train_line[-1] - predicted

                self.weights[0] = self.weights[0] + self.learning_rate*error*-1.0
                for i in range(len(train_line) - 1):
                    self.weights[i + 1] = self.weights[i + 1] + self.learning_rate*error*train_line[i]

    def test(self, ind):
        """
        Tests a single problem instance
        :param ind: Index of the problem
        :return: The predicted result
        """
        return self.predict(self.testset[ind])

    def __str__(self):
        s = ""
        s = s + "Perceptron data: \n"
        s = s + "\tLearning rate: " + str(self.learning_rate) + "\n"
        s = s + "\tNumber of epochs: " + str(self.n_epochs) + "\n"
        s = s + "\tWeigths"

        return s
