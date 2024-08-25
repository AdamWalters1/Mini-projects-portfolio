# ext_date_type.py
from date_type import DateType

class ExtDateType(DateType):
    """
    Class to handle extended date operations
    """
    MONTH_NAMES = ["", "January", "February", "March", "April", "May", "June", "July",
                   "August", "September", "October", "November", "December"]

    def __init__(self, month=1, day=1, year=1900):
        super().__init__(month, day, year)
        self.month_name = self.MONTH_NAMES[self.month]

    def set_month(self, month):
        super().set_month(month)
        self.month_name = self.MONTH_NAMES[month]

    def set_date(self, month, day, year):
        super().set_date(month, day, year)
        self.month_name = self.MONTH_NAMES[month]