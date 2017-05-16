import os
import numpy as np
class bayes:
	def __init__(self):
		self._criteria='NB'
	def _create_voc(self,datalist):
		vocabu=set([])
		for line in datalist:
			vocabu=vocabu | set(line)
		return list(vocabu)
	
