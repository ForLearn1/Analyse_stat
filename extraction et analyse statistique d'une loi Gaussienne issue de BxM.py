# -*- coding: utf-8 -*-
"""
Created on Wed Jan  8 00:39:16 2025

@author: FALL Abdoul Ahad
"""

import pandas as pd

#========== J'ai utilisé Pandas pour me permettre de charger le fichier CSV =================
""" Dont il faudra bien spécifier le chemin d'accès au fichier afin que 
 programme puisse marcher bien """
 
file_path = 'C:/Users/User/Desktop/Gauss/sample_data.csv' # Il faudra penser à modifier le chemin d'accès à ce fichier
data = pd.read_csv(file_path, header=None)

#=========================================================================
# Calculer la moyenne et l'écart type
mean_value = data[0].mean()
std_deviation = data[0].std() 

#========================================================================
# Calculer la probabilité de tirer un élément spécifique
# Exemple : Probabilité de tirer la valeur 0.1
specific_value = 0.1

count_specific_value = (data[0] == specific_value).sum()

total_values = len(data)

probability_specific_value = count_specific_value / total_values
