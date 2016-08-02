import pandas as pd

'''
Data sharing structure that is used in between sever
data processor and modeler. the singleton function that should
ever be called once, currently there is no policy enhancing logics 
to prevent multiple calls, that could be one improvement.
'''

def init():
	global dataf, ctr, background_controller, client_controller
	dataf = pd.DataFrame()
	ctr = 0
	background_controller = True
	client_controller = True 
