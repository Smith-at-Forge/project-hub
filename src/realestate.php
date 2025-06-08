<!doctype html>
<!--
Hallo, hier ist meine Loesung zur Aufgabe mit dem Code XX1-K02.
Weil das Heft schon veraltet ist, habe ich einiges ueberarbeitet und an PHP 8.2 angepasst.
Am Ende des Textes fasse ich alles zusammen, was ich verwendet habe.
Ansonsten habe ich, soweit ich das beurteilen kann, alles durchgetestet
	und es funktioniert alles. (Wenn Sie ein Datensatz aendern moechten,
	waehlen Sie im Dropdown die entsprechende Option.)
Da es doch viele Kombinationen und Moeglichkeiten gibt,
	habe ich vielleicht auch etwas uebersehen.
	Falls etwas nicht funktioniert wie es soll, ich arbeite es gerne nach.
Zur Aufgabe, diese finden Sie ab Zeile 227 und 242,
	ich habe sie jeweils mit Kommentaren markiert. Fuer das Loeschen
	habe ich Abfrage clientseitig umgesetzt. Die etwas umstaendlichere
	Variante koennten wir durch einen extra Round-Trip zum Server umsetzen.
Abschliessend die wichtigsten Parameter, um einen Vergleich zu ermoeglichen:
	OS: Windows 10
	Xampp: 3.3.0
	PHP: 8.2
	Webbrowser: Firefox Mozilla
	zugang.php: $host= $user= $password=
	Tabelle in der Datenbank anlegen:
CREATE TABLE Person (
PersonID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
Anrede VARCHAR(30) NOT NULL,
Name VARCHAR(30) NOT NULL,
AdressID INTEGER UNSIGNED NOT NULL REFERENCES Adresse.AdressID,
GeburtsDatum DATE,
EMail VARCHAR(30),
Wohnhaus INTEGER UNSIGNED NOT NULL REFERENCES Haus.HausID
) ENGINE=INNODB;

CREATE TABLE Haus (
HausID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
AdressID INTEGER UNSIGNED NOT NULL REFERENCES Adresse.AdressID,
WohnungsZahl INTEGER NOT NULL DEFAULT 1,
Besitzer INTEGER UNSIGNED NOT NULL REFERENCES Person.PersonID
) ENGINE=INNODB;

CREATE TABLE Adresse (
AdressID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
PLZOrt VARCHAR(30) NOT NULL,
StrasseHNr VARCHAR(30) NOT NULL
) ENGINE=INNODB;

-->
<html>

	<head>
		<meta charset="utf-8">

		<title>
		Beispiel DB immo
		</title>

	</head>

<body>
	<?php
	include("zugang.php");
	$vID = @mysqli_connect($host,$user,$password);
	if (!$vID) {
	echo "<p>Verbindungsfehler!</p>"; exit();
	}
	@mysqli_select_db($vID, "immo");

	echo "<a href='immo.php?h=0'>neues Haus anlegen!</a><br>";

	if ( (!$_POST) && (!$_GET) ) {

	$a = "SELECT HausID, StrasseHNr, PLZOrt FROM Haus,Adresse ";
	$a = $a."WHERE Haus.AdressID=Adresse.AdressID ";
	$a = $a."ORDER BY StrasseHNr";

	$eID = @mysqli_query($vID, $a);
	if (!$eID) {
	echo "<p>Keine Häuser gefunden!</p>"; exit();
	}

	while ($Zeile = @mysqli_fetch_row($eID)) {
	echo "<a href='immo.php?h=",$Zeile[0],"'>";
	echo $Zeile[1],", ",$Zeile[2],"</a><br>";
	}

	@mysqli_free_result($eID);
	} else {
	//..................................................................
		if (isset($_GET['h']) && $_GET['h']==0) { // $_GET['h']==0 

		echo "<p>Neuanlage Haus:</p>";
		echo "<form action='immo.php' method='post'
		style='text-align:center'>"; // oeffne form, action >>> setze Attribut auf immo.php

		echo "<label for='adresse'>Adresse: </label>";
		echo "<select name='adresse'>"; // DropDownMenu
		echo "<option value='0'>unbekanntes Haus</option>";

		$a = "SELECT AdressID, StrasseHNr, PLZOrt FROM Adresse";
		$a = $a." ORDER BY StrasseHNr";
		$eID = @mysqli_query($vID, $a);
		if ($eID) {
			while ($Zeile = @mysqli_fetch_row($eID)) {
			echo "<option value='",$Zeile[0],"'>";
			echo $Zeile[1],", ",$Zeile[2],"</option>";
			}
		}
		@mysqli_free_result($eID);

		echo "</select><br>"; // DropDownMenu Ende

		echo "<label for='StrasseHnr'>Straße Hausnummer: </label>";
		echo "<input name='StrasseHNr'><br>";

		echo "<label for='PLZOrt'>Postleitzahl und Ort: </label>";
		echo "<input name='PLZOrt'><br>";

		echo "<label for='Anzahl'>Anzahl der Wohnungen: </label>";
		echo "<input name='Anzahl' value='1'><br>";

		echo "<label for='Besitzer'>Besitzer: </label>";
		echo "<select name='Besitzer'>";
		echo "<option value='0'>unbekannter Besitzer</option>";

		$a = "SELECT PersonID, Name, PLZOrt FROM Person,Adresse";
		$a = $a." WHERE Person.AdressID=Adresse.AdressID";
		$a = $a." ORDER BY Name, PLZOrt";
		$eID = @mysqli_query($vID, $a);
		if ($eID) {
			while ($Zeile = @mysqli_fetch_row($eID)) {
			echo "<option value='",$Zeile[0],"'>";
			echo $Zeile[1]," (",$Zeile[2],")</option>";
			}
		}
		echo "</select><br>";

		@mysqli_free_result($eID);

		echo "<input name='ET' type='hidden' value='h'>";
		echo "<input name='ID' type='hidden' value='0'>";

		echo "<input type='submit' value='eintragen'>";
		echo "</form>";

		} // $_GET['h']==0
	//..................................................................
		if (isset($_GET['h']) && $_GET['h']>0) {  // $_GET['h']>0
		$HausID=$_GET['h'];

		$a = "SELECT AdressID,WohnungsZahl,Besitzer";
		$a = $a." FROM Haus WHERE HausID=".$HausID;

		$eID = @mysqli_query($vID, $a);
		if ($eID) {
			$row = @mysqli_fetch_row($eID);
			$Adresse = $row[0];
			$Anzahl = $row[1];
			$Besitzer = $row[2];
			}
		@mysqli_free_result($eID);

		$a = "SELECT StrasseHNr, PLZOrt FROM Adresse";
		$a = $a." WHERE AdressID=".$Adresse;

		$eID = @mysqli_query($vID, $a);
		if ($eID) {
			$row = @mysqli_fetch_row($eID);
			$StrasseHNr = $row[0];
			$PLZOrt = $row[1];
			}
		@mysqli_free_result($eID);

		echo "<p>",$StrasseHNr,", ",$PLZOrt,"</p>";
		echo "<form action='immo.php' method='post'
		style='text-align:center'>";

		echo "<label for='adresse'>Adresse:</label>";
		echo "<select name='adresse'>"; // Beginn DropDown eins
		echo "<option value='0'>Adress-Änderung</option>";

		$a = "SELECT AdressID, StrasseHNr, PLZOrt FROM Adresse";
		$a = $a." ORDER BY StrasseHNr";
		$eID = @mysqli_query($vID, $a);
		if ($eID) {
			while ($Zeile = @mysqli_fetch_row($eID)) {
				echo "<option value='",$Zeile[0],"'";
				if ($Zeile[0]==$Adresse) {echo " selected";}
				echo ">",$Zeile[1],", ",$Zeile[2],"</option>";
				}
			}
		@mysqli_free_result($eID);
		echo "</select><br>"; // Ende DropDown eins

		echo "<label for='StrasseHNr'>Straße Hausnummer: </label>";
		echo "<input name='StrasseHNr' value='",$StrasseHNr,"'><br>";

		echo "<label for='PLZOrt'>Postleitzahl und Ort: </label>";
		echo "<input name='PLZOrt' value='",$PLZOrt,"'><br>";

		echo "<label for='Anzahl'>Anzahl der Wohnungen: </label>";
		echo "<input name='Anzahl' value='",$Anzahl,"'><br>";

		echo "<label for='Besitzer'>Besitzer: </label>";
		echo "<select name='Besitzer'>"; // Beginn DropDown zwei
		echo "<option value='0'>unbekannter Besitzer</option>";

		$a = "SELECT PersonID, Name, PLZOrt FROM Person,Adresse";
		$a = $a." WHERE Person.AdressID=Adresse.AdressID";
		$a = $a." ORDER BY Name, PLZOrt";
		$eID = @mysqli_query($vID, $a);
		if ($eID) {
			while ($Zeile = @mysqli_fetch_row($eID)) {
				echo "<option value='",$Zeile[0],"'";
				if ($Zeile[0]==$Besitzer) {echo " selected";}
				echo ">",$Zeile[1]," (",$Zeile[2],")</option>";
				}
			}
		echo "</select><br>"; // Ende DropDown zwei

		@mysqli_free_result($eID);

		echo "<input name='ET' type='hidden' value='h'>";
		echo "<input name='ID' type='hidden' value='".$HausID."'>";

		echo "<input type='submit' value='ändern'>";
		echo "</form>";

		// Typ A, Aufgabe 1
		// Loeschformular
		echo "<form action='immo.php' method='post' onsubmit=\"return confirm('Soll der Datensatz zum Haus wirklich gelöscht werden?')\" style='text-align:center'>";
		echo "<input name='ET' type='hidden' value='h'>";
		echo "<input name='ID' type='hidden' value='".$HausID."'>";
		echo "<input name='action' type='hidden' value='delete'>";
		echo "<input type='submit' value='löschen'>";
		echo "</form>";
		// Loeschformular Ende

		} // $_GET['h']>0

	//..................................................................
		if (isset($_POST['ET']) && $_POST['ET']=='h') { // Entitätstyp Haus
			
		// Typ A, Aufgabe 2
		// PHP-Script: Loeschen
		if (isset($_POST['action']) && $_POST['action'] == 'delete') {
			$HausID = $_POST['ID'];

			// Wenn bestaetigt, fuehre den Loeschvorgang aus
			$a = "DELETE FROM Haus WHERE HausID=".$HausID;
			$eID = @mysqli_query($vID, $a);
			if ($eID) {
				echo "Der Datensatz zum Haus wurde erfolgreich gelöscht.<br>";
			} else {
				echo "Es gab einen Fehler beim Löschen des Datensatzes.<br>";
			}

			// Weiterleitung zur Uebersicht
			echo "<a href='immo.php'>Zurück zur Übersicht.</a>";
			exit; // Stoppe die Ausfuehrung weiteren Codes, da nach einem Loeschvorgang die nachfolgenden Updates nicht relevant sind.
		}
		// PHP-Script: Loeschen, Ende

		$HausID = $_POST['ID'];
		if ($HausID==0) { // neues Haus
			$a = "INSERT INTO Haus (AdressID,Besitzer)";
			$a = $a." VALUES (0,0)";
			$eID = @mysqli_query($vID, $a);
			if($eID) {
				$HausID = @mysqli_insert_id($vID);
				}
			}

		$AdressID = $_POST['adresse'];
		if ($AdressID==0) { // neue Adresse
			$StrasseHNr = $_POST['StrasseHNr'];
			$PLZOrt = $_POST['PLZOrt'];
			if (empty($PLZOrt)) {
				$AdressID=0;
				echo "Postleitzahl/Ort darf nicht leer sein! Bitte korrigieren!";
				}
			else {
				$a = "INSERT INTO Adresse (StrasseHNr,PLZOrt)";
				$a = $a." VALUES ('".$StrasseHNr."','".$PLZOrt."')";
				$eID = @mysqli_query($vID, $a);
				$AdressID = @mysqli_insert_id($vID);
				}
			}

		$Anzahl = intval($_POST['Anzahl']);
		if (!($Anzahl > 0)) {
			$Anzahl=0;
			echo "Die Anzahl wurde nicht erkannt. Bitte korrigieren!";
			}
		$Besitzer = $_POST['Besitzer'];

		$a = "UPDATE Haus SET ";
		$a = $a." AdressID=".$AdressID.",";
		$a = $a." Wohnungszahl=".$Anzahl.",";
		$a = $a." Besitzer=".$Besitzer;
		$a = $a." WHERE HausID=".$HausID;

		$eID = @mysqli_query($vID, $a);

		echo "Die Änderungen wurden gespeichert.<br>";
		echo "<a href='immo.php?h=".$HausID."'>";
		echo "Zurück zum Haus!</a>";

		} // Entitätstyp Haus
	}

	@mysqli_close($vID);
	?>

</body>

</html>