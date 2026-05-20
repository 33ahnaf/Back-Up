class Train:
    company = "Bangladesh Railways"
    
    def __init__(self, train_No, seat_No, number_of_available_seat, from_, to_):
        self.train_No = train_No
        self.seat_No = seat_No
        self.number_of_available_seat = number_of_available_seat
        self.from_ = from_
        self.to_ = to_

    def book_ticket(self):
        print(f"Ticket booked succesfully!\nTrain No.: {self.train_No}\tSeat No.: {self.seat_No}")

    def getStatus(self):
        print(f"\nTrain No.: {self.train_No}\tAvailable seats: {self.number_of_available_seat}")

    def getFareInfo(self):
        print(f"\nTrain No.: {self.train_No}\tFrom: {self.from_}\tTo: {self.to_}\tCompany: {self.company}")

train_a = Train(2947, 43, 73, "Tetulia", "Teknaf")
train_a.book_ticket()
train_a.getStatus()
train_a.getFareInfo()