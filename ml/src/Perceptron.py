import random


class Perceptron:
    def __init__(self, trainset, testset, learning_rate, n_epochs):
        self.trainset = trainset
        self.testset = testset
        self.learning_rate = learning_rate
        self.n_epochs = n_epochs
        self.weights = [0.0 for i in range(len(trainset[0]))]

    def predict(self, train_line):
        activate = self.weights[0]  # First element is the "ground"

        for i in range(len(train_line) - 1):
            activate = activate + self.weights[i + 1]*train_line[i]

        return 1.0 if activate >= 0.0 else 0.0

    def train(self):
        for epoch in range(self.n_epochs):
            random.shuffle(self.trainset)
            for train_line in self.trainset:
                predicted = self.predict(train_line)

                error = train_line[-1] - predicted

                self.weights[0] = self.weights[0] + self.learning_rate*error  # "ground" is set to 1, so simple multiply
                for i in range(len(train_line) - 1):
                    self.weights[i + 1] = self.weights[i + 1] + self.learning_rate*error*train_line[i]

    def test(self, ind):
        """
        Tests a single problem instance
        :param ind: Index of the problem
        :return: The predicted result
        """
        return int(self.predict(self.testset[ind]))

    def __str__(self):
        s = ""
        s = s + "Perceptron data: \n"
        s = s + "\tLearning rate: " + str(self.learning_rate) + "\n"
        s = s + "\tNumber of epochs: " + str(self.n_epochs) + "\n"
        s = s + "\tWeigths"

        return s
