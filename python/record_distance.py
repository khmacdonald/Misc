import difflib

def distance ( str1, str2 ) :
    '''
    This is a simple wrapper for the SequenceMatcher function
    found in the difflib library.  A wrapper is used in case
    later you want to use a different difference function. 
    Since SequenceMatcher returns sort of a probability that
    two strings are similar, with 1.0 being an exact match,
    subtract that number from 1.0 to get a more distance like
    number.
    '''
    return 1.0 - difflib.SequenceMatcher(None,str1,str2).ratio()

'''
Given two records that have five strings that need to be compared:
doc_num     - The document number
case_num    - The case number
issue_date  - The issue date for the document
first_name  - The first name
last_name   - The last name
'''
def record_distance ( record1, record2 ) :
    '''
    Sum the distances for each of the five strings in the records
    being compared.  The distance function being used returns a number
    between 0.0 and 1.0.  The more similar the strings are, the lower
    the distance.  The distance between the same string is 0.0
    '''
    dist = distance(record1.doc_num,record2.docnum)
    dist += distance(record1.case_num,record2.case_num)
    dist += distance(record1.issue_date,record2.issue_date)
    dist += distance(record1.first_name,record2.first_name)
    dist += distance(record1.last_name,record2.last_name)
    return dist

def is_same_record ( record1, record2, threshold ) :
    '''
    Given two records if the 'distance' is above some threshold, then
    the two records are said to be the same.  The smaller the record_distance
    the more similar the strings are.  A record_distance of 0.0 means
    all strings in the record match exactly.
    '''
    if record_distance(record1,record2) <= threshold:
        return True
    return False


