class Perceptron:
    def __init__(self, trainset, testset, learning_rate, n_epochs):
        self.trainset = trainset
        self.testset = testset
        self.learning_rate = learning_rate
        self.n_epochs = n_epochs

    def train(self):
        pass

    def test(self):
        pass

    def __str__(self):
        s = ""
        s = s + "Perceptron data: \n"
        s = s + "\tLearning rate: " + str(self.learning_rate) + "\n"
        s = s + "\tNumber of epochs: " + str(self.n_epochs) + "\n"

        return s
