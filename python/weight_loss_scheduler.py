#!/usr/local/bin/python2.7

import datetime
from dateutil.relativedelta import relativedelta
import os
import sys

argv = sys.argv
argc = len(argv)

def build_chunk_string ( start_weight, monthly_weight, 
                         end_weight, loss_time, stable_time, dt ):
    #date_fmt = "%Y-%m"
    date_fmt = "%b %Y"
    date_str = dt.strftime(date_fmt)
    loss = start_weight - end_weight
    mloss = loss / float(loss_time)   # monthly weight loss
    wloss = mloss / 4.0          # weekly weight loss
    oline = '%s - Starting at %d lbs, lose %d lbs' % \
             (date_str,start_weight,loss)
    oline = '%s\n          %3.1f per month, %3.1f per week' % \
             (oline,mloss,wloss)

    for mweight in monthly_weight:
        dt = dt + relativedelta(months=1)
        date_str = dt.strftime(date_fmt)
        oline = "%s\n    %s %d lbs" % (oline,date_str,mweight)

    dt = dt + relativedelta(months=1)
    date_str = dt.strftime(date_fmt)
    oline = "%s\n    %s %d lbs" % (oline,date_str,end_weight)
    oline = "%s\n    Hold at %d lbs for %d months" % \
             (oline,end_weight,stable_time)
    dt = dt + relativedelta(months=stable_time)

    return oline, dt

def compute_loss_months ( start_weight, end_weight, loss_time ):
    # Total loss in this period
    loss = start_weight - end_weight

    # Get monthly weight loss
    monthly_loss = loss // loss_time
    monthly_weight = []

    # Compute weight at the end of each month
    for k in range(loss_time-1):
        start_weight = start_weight - monthly_loss
        monthly_weight.append(start_weight)

    return loss, monthly_weight

def schedule( start_weight, end_weight, loss_time, stable_time ):
    current_weight = start_weight
    dt = datetime.datetime.today()
    dt = dt + relativedelta(months=1)
    while current_weight>end_weight:
        # Lose no more than 10% of current weight in any 
        # weight loss period.
        current_end_weight = int(current_weight * 0.9) 
        if current_end_weight < end_weight:
            current_end_weight = end_weight

        # Compute the losses in this time period
        loss, monthly_weight = compute_loss_months(current_weight,\
                                                   current_end_weight,\
                                                   loss_time)

        # Create the output string for this weight loss chunk
        chunk, dt = build_chunk_string(current_weight,\
                                       monthly_weight,\
                                       current_end_weight,\
                                       loss_time,stable_time,dt)
        print("%s\n\n" % chunk)
        
        # The new current weight is the old end weight
        current_weight = current_end_weight

        # End while
        
    return True

def main ( ):
    if 5!=argc:
        print("USAGE: %s <starting weight> <ending Weight>"
              "<loss time (months)> <stable time(months)>" % argv[0])
        return False
    start_weight = int(argv[1]) # start weight
    end_weight   = int(argv[2]) # end weight
    loss_time    = int(argv[3]) # weight loss time frame chunk (months)
    stable_time  = int(argv[4]) # weight stabilization time frame chunk (months)

    # Compute and print the weight loss schedule
    schedule(start_weight,end_weight,loss_time,stable_time)

if __name__=="__main__":
    main()



