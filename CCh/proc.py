import numpy as np

'''
This module is for modlers
'''

'''
the trend catching module that provides calculation for data thats sent in
the strategy is simply buy when t+1 price > t avg+t sigma sell when t+1 price < t avg - t sigma
hold otherwise.

input: a list of prices and the previous total position

output:new position and its PnL

Inp: this can be ommited for faster avg and sigma function
for purpose of this task only

'''

def strategy1(priceList,pos_old):
  ''' Trading strategy 1 that takes in a 24-hour bitcoin price series S(t-1439) to S(t+1) and pos(t)
      It first computes PnL(t+1); then S_avg(t), sigma(t), and pos(t+1).
  '''
  
  S = np.array(priceList)
  PnL = pos_old * (S[-1] / S[-2] -1)
  S_avg = np.mean(S[:-1])
  sigma = np.std(S[:-1])
  if S[-2] > S_avg + sigma:
    pos_new = pos_old + 1
  elif S[-2] < S_avg - sigma:
    pos_new = pos_old - 1
  else:
    pos_new = pos_old
  return pos_new, PnL