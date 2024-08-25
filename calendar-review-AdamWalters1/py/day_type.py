# day_type.py
class DayType:
    """
    Class to handle day operations
    """
    WEEK_DAYS = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
                 "Saturday"]

    def __init__(self, week_day="Sunday"):
        self.set_day(week_day)

    def set_day(self, week_day):
        if week_day in self.WEEK_DAYS:
            self._week_day = week_day
        else:
            self._week_day = "Sunday"

    @property
    def week_day(self):
        return self._week_day

    def next_day(self):
        index = (self.WEEK_DAYS.index(self.week_day) + 1) % 7
        return self.WEEK_DAYS[index]

    def prev_day(self):
        index = (self.WEEK_DAYS.index(self.week_day) - 1) % 7
        return self.WEEK_DAYS[index]

    def add_day(self, n_days):
        index = (self.WEEK_DAYS.index(self.week_day) + n_days) % 7
        self._week_day = self.WEEK_DAYS[index]