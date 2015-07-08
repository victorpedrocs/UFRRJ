
# coding: utf-8

# # Ajuste de Curvas pelo método dos Quadrados Mínimos
# 

# 
# # Introdução
# 
# Utilizado quando a interpolação não é aconselhável, isto é:
# 1. É preciso obter um valor aproximado da função em algum ponto fora do intervalo de tabelamento, ou seja, quando se quer extrapolar;
# 1. os valores tabelados são resultados de algum experimento físico de alguma pesquisa, porque, nestes casos, estes valores poderão conter erros inerentes que, em geral, não são previsíveis.
# 
# ### Caso Discreto (livro)
# O problema do ajuste de curvas no caso em que temos uma tabela de pontos $(x_1, f(x_1)), (x_2, f(x_2), ..., (x_m, f(x_m))$ com $ x_1, x_2, ..., x_m$, pertencentes a um intervalo $[a,b]$, consite em : "escolhidas m funções $g_1(x), g_2(x), ..., g_n(x)$, contínuas em $[a,b]$, obter $n$ constantes $\alpha_1, \alpha_2, ..., \alpha_n$, tais que a função $\phi(x) = \alpha_{1}g_1(x) + \alpha_{2}g_2(x) + \alpha_{n}g_n(x)$ se aproxime ao máximo de $f(x)$ .
# 
# Dizemos que este é um modelo matemático linear porque os coeficientes a determinar, $\alpha_1, \alpha_2, ..., \alpha_n$, aparecem linearmente, embora as funções $g_1(x), g_2(x), ..., g_n(x)$ possam ser funções não lineares de $x$, como por exemplo, $g_1(x) = e^x, g_2(x) = (1+x^2)$ etc.

# In[2]:

import matplotlib.pyplot as pyplt
import numpy as np
from scipy import linalg

# definicao dos pontos no plano cartesiano ou diagrama de dispersão
x = [-1, -0.75, -0.6, -0.5, -0.3, 0, 0.2, 0.4, 0.5, 0.7, 1] # x
y = [2.05, 1.153, 0.45, 0.4, 0.5, 0, 0.2, 0.6, 0.512, 1.2, 2.05] #f(x)

# plot dos pontos definidos acima no formato de pontos pretos
pyplt.plot(x,y,'ko')
# definicao do intervalo
pyplt.axis([-2, 2, -1, 3])
pyplt.grid(True)


# ## Método dos Quadrados Mínimos (livro)
# ### Caso discreto
# 
# Sejam dados os pontos $(x_1, f(x_1)), (x_2, f(x_2)), ..., (x_m, f(x_m))$ e as funções $g_1(x), g_2(x),...,g_n(x)$ escolhidas de alguma forma.
# 
# Consideraremos que o número de pontos $m$, tabelados, é sempre maior ou igual a $n$ o número de funções escolhidas ou o número de coeficientes $\alpha_i$ a se determinar.
# 
# O objetivo é encontrar coeficientes $\alpha_i$ tais que a função: $$\phi(x) = \sum_{i=1}^{n}{\alpha_{i}g_i(x)}$$ se aproxime ao máximo  de $f(x)$.
# 
# Seja $d_k = f(x_k) = \phi(x_k)$ o desvio em $x_k$ desejamos que $d_k$ seja mínimo para todo $k = 1, 2, ..., m$.
# 
# O método dos quadrados mínimos consiste em escolher os $\alpha_j$ de forma que a soma dos quadrados dos desvios seja mínima. Logo, se a soma $\sum_{k=1}^{m}d_k^2 = \sum_{k=1}^{m}(f(x_k) - \phi(x_k))^2$ é mínima, cada parcela $[f(x_k) - \phi(x_k)]^2$ é pequena, de onde cada desvio $[f(x_k) - \phi(x_k)]$ é mínimo.
# 
# Portanto dentro dos quadrados mínimos, os coeficientes $\alpha_k$ que fazem com que $\phi(x)$ se aproxime ao máximo de $f(x)$, são os que minimizam a função
# $$F(\alpha_1, \alpha_2,...,\alpha_n) = \sum_{k=1}^{m}[f(x_k) - \phi(x_k)]^2 = \sum_{k=1}^{m}[f(x_k) - \alpha_{1}g_1(x_k) - \alpha_{2}g_2(x_k) - \alpha_{n}g_n(x_k)]^2$$
# 
# Usando Cálculo, sabemos que, para obter um ponto mínimo de uma função, temos que encontrar seus pontos críticos, ou seja,  os $(\alpha_1, \alpha_2, ..., \alpha_n$  tais que
# $$\left.\frac{\delta F}{\delta \alpha_j}  \right | (\alpha_1, \alpha_2, ..., \alpha_n) = 0, j, = 1, 2, ...,n$$
# Calculando estas derivadas parciais para cada j = 1, 2, ..., n, temos:
# $$ \left.\frac{\delta F}{\delta \alpha_j}  \right | (\alpha_1, \alpha_2, ..., \alpha_n) = 2 \sum_{k=1}^{m}{[f(x_k) - \alpha_{1}g_1(x_k),...,\alpha_{m}g_m(x_k)][-g_j(x_k)]}$$.
# Inpondo a condição
# $$ \frac{\delta F}{\delta \alpha_j} = 0, j = 1, 2, ..., n $$
# temos
# $$ \sum_{k=1}^{m}{[f(x_k) - \alpha_{1}g_1(x_k),...,\alpha_{m}g_m(x_k)][-g_j(x_k)]} = 0,j = 1,2,...,n $$
# Assim, um sistema linear com n equaçõs n ingógnitas $\alpha_1, \alpha_2, ..., \alpha_n$, que pode ser escrito na forma matricial como $A\alpha = b$.

# ### Implementação
# 
# Feito o diagrama de disperção, deve ser ajustada por uma parábola que passa pela origem, ou seja, $f(x) \approx \phi(x) = \alpha x^2$. Neste caso (parábola) temos apenas uma função $g(x) = x^2$.

# In[3]:

def g(x):
    return x**2


# Definiremos também a função somatório que efetua $ \sum_{k=1}^{m}{g_j(x_k)g_i(x_k)} $

# In[4]:

def somatorio( g_column, g_row, x_array ):
    result = 0
    for x in (x_array):
        result += g_row(x)*g_column(x)
    return result


# Também é necessário definir um somatório para $\sum_{k=1}^{m}{f(x_k)g_n(x_k)}$

# In[5]:

def somatoriof( y_array, g, x_array):
    result = 0
    for y, x in zip(y_array, x_array):
        result += y*g(x)
    return result


# Agora a função que resolve o sistema de equações

# In[6]:

def square_minimum(g_array, x_array, y_array):
    A = []
    b = []
    
    for line in xrange(0,len(g_array)):
        rowA = []
        for column in xrange(0,len(g_array)):
            rowA.append(somatorio(g_array[column], g_array[line], x_array))
        
        A.append(rowA)
        b.append(somatoriof(y_array, g_array[line], x_array))
    
    return np.linalg.solve(A,b)


# Agora podemos solicitar a solução do sistema para o exemplo dado no início

# In[8]:

g_array = [g]
solution = square_minimum(g_array, x, y)

print solution


# Agora, com este resultado, podemos plotar a parábola com a função de resultado

# In[15]:

xnp = np.array(x)
equation = eval(str(solution[0])+'*xnp**2')

pyplt.plot(x,y,'ko')
pyplt.plot(x, equation)
pyplt.axis([-1.5, 1.5, -0.5, 2.5])
pyplt.grid(True)
pyplt.show()


# ## Referências
# * Cálculo Numérico: Aspectos Teóricos Computacionais - Vera Lucia Da Rocha Lopes; Marcia A. Gomes Ruggiero 
# * [Python numpy.linalg](http://docs.scipy.org/doc/numpy/reference/routines.linalg.html)
