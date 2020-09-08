def largestoflist(lists, counter = 0, highest = 0) -> int:
    if counter == len(lists):
        print(highest)
        return highest
    if lists[counter] >= highest:
        highest = lists[counter]
    largestoflist(lists, counter + 1, highest)

largestoflist([0,14,20,5,1,6,9])