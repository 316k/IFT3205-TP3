# TP 1 Traitement de signal

Remis par :
* Nicolas Hurtubise
* Guillaume Riou


## 2.2

Lors d'une convolution, le facteur de normalisation pour garder la moyenne de l'image est de 1/∑[coefficients de la matrice de convolution]

Puisque l'interpolation spectrale est équivalente à convoluer avec un noyau d'interpolation dans le domaine spatial, le facteur de normalisation serait simplement :

1/∑[coefficients du noyau d'interpolation]


## 2.3

Une façon serait de calculer la TF de l'image, de la placer au centre d'une image plus grande et d'extrapoler les bords pour tenter de retrouver des hautes fréquences plausibles pour cette image.

Il serait peut-être utile d'appliquer un dégradé sur les fréquences extrapolées, afin d'éviter de donner trop d'importance aux fréquences les plus éloignées des fréquences connues.


## 3.3

Le seuillage dur permet de garder seulement les fréquences dominantes de l'image et d'ainsi arriver à une simplification de la texture recherchée. Une FFT inverse est par définition une interpolation optimale, ce qu'on utilisera pour remplacer pixels dégradés par quelque chose de plus proche de l'image recherchée.

Commencer par utiliser la TF de l'image entière permet d'obtenir une texture grossière qui sera très peu influancée par la dégradation à éliminer. En répétant le processus en encerclant la dégradation et en diminuant la taille de la fenêtre de FFT utilisée, on peut avoir une approximation plus précise de la texture locale autour de la dégradation.

