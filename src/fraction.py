"""
Aufgaben
        Methode ggt(a, b)
                ggt() bei Erzeugung eines Objekts so anwenden,
                dass Zähler und Nenner des gekürzten Bruchs gespeichert werden
        Methode, um Operator '==' auf Brüche anzuwenden
                vergleiche beide Zähler, als auch beide Nenner
"""


class Bruch:
    def __init__(self, zaehler=1, nenner=1):
        self.z = zaehler
        self.n = nenner

    def __str__(self):
        return str(self.z) + "/" + str(self.n)

    # erweitere class Bruch
    def ggt(self, a, b):
        if b == 0:
            return a
        else:
            return self.ggt(b, a % b)

    def __eq__(self, other):
        z1 = self.z / self.ggt(self.z, self.n)
        n1 = self.n / self.ggt(self.z, self.n)
        z2 = other.z / self.ggt(other.z, other.n)
        n2 = other.n / self.ggt(other.z, other.n)
        return z1 == z2 and n1 == n2


# Hauptrogramm
b5 = Bruch(30, 6)
print("b5:", b5)

z = 36
n = 6
b6 = Bruch(z, n)
b6.z, b6.n = z / b6.ggt(z, n), n / b6.ggt(z, n)
print("b6 (gekürzt):", b6)

print("b5 und b6 haben den gleichen Wert:", b5 == b6)

"""
Weitere Optimierungen: 'float' zu 'int' wandeln und eine Input-Abfrage
einbauen, um die Brüche selbst einzugeben. Dazu würde ich zusätzlich
ein Try-Except Block in einer Schleife einbauen, falls man sich
vertippt bei Eingabe.
"""
