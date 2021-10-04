# Explicació del experiment

En aquest exemple, hem volgut fer 2 cops la mateixa acció, utilitzant diferents tipos de crides, per tal de demostrar que efectivament les crides a sistema son mes lentes que les crides a procediment. Hem decidit fer un exemple simple, amb un printf y un execv que faci un echo.

Com veiem, les crides a procediment son menys costoses que les crides a sistema. Una crida a una proceiment, com la que fem al exemple amb el printf son crides un tros de codi de l'espai de l'usuari. En canvi, una crida a sistema apunta a un espai privilegiat, reservat pel kernel, com fem amb el execv. Aquesta separació aporta molta seguretat al sistema operatiu, però fa que una crida al sistema sigui molt més costosa.

Degut a lo explicat anteriorment, podem veure com un execv fent un echo es més lent que un printf.
