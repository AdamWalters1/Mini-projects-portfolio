def sequential_search(arr, target):
    """Search for target in arr. Returns index of target or -1 if not found."""
    for index, value in enumerate(arr):
        if value == target:
            return index
    return -1

# Example usage
