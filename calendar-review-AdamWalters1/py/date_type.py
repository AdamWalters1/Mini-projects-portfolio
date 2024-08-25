# date_type.py
import calendar
from datetime import datetime, timedelta

class DateType:
    """
    Class to handle date operations
    """

    def __init__(self, month=1, day=1, year=1900):
        self.set_date(month, day, year)

    def set_date(self, month, day, year):
        self._year = year if year >= 1 else 1900
        self._month = month if 1 <= month <= 12 else 1
        self._day = day if 1 <= day <= 31 else 1
        self.adjust_day()

    def set_month(self, month):
        self._month = month if 1 <= month <= 12 else 1
        self.adjust_day()

    def set_day(self, day):
        self._day = day
        self.adjust_day()

    def set_year(self, year):
        self._year = year if year >= 1 else 1900
        self.adjust_day()

    @property
    def month(self):
        return self._month

    @property
    def day(self):
        return self._day

    @property
    def year(self):
        return self._year

    def is_leap_year(self):
        return self.year % 4 == 0 and (
                    self.year % 100 != 0 or self.year % 400 == 0)

    def adjust_day(self):
        days_in_month = calendar.monthrange(self.year, self.month)[1]
        self._day = min(self.day, days_in_month)

    def number_of_days_passed(self):
        current_date = datetime(self.year, self.month, self.day)
        start_of_year = datetime(self.year, 1, 1)
        return (current_date - start_of_year).days + 1

    def number_of_days_left(self):
        end_of_year = datetime(self.year, 12, 31)
        current_date = datetime(self.year, self.month, self.day)
        return (end_of_year - current_date).days

    def increment_date(self, n_days):
        current_date = datetime(self.year, self.month, self.day)
        new_date = current_date + timedelta(days=n_days)
        self._year, self._month, self._day = new_date.year, new_date.month, new_date.day
