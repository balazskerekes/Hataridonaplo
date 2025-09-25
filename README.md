# Határidőnapló – Felhasználói dokumentáció

## 📌 Program célja
A határidőnapló program lehetőséget biztosít a felhasználónak események **tárolására, szerkesztésére, törlésére, megjelenítésére és keresésére**.

## ▶️ Kezelés
A program indítása után a felhasználó a főmenüt látja.  
Minden művelet után a program megkéri a felhasználót, hogy nyomjon meg egy billentyűt a folytatáshoz.

---

## 🗂️ Főmenü
1. Új rekord létrehozása  
2. Rekord módosítása  
3. Rekord törlése  
4. Események keresése  
5. Események listázása  
6. Kilépés  

A felhasználó a megfelelő szám beírásával választ.

---

## ✏️ Új rekord létrehozása
A következő adatokat kell megadni:

- **Esemény neve**: szöveg  
- **Dátum**: `ÉÉÉÉ/HH/NN` formátumban  
- **Kezdő időpont**: `ÓÓ:PP` formátumban  
- **Befejező időpont**: `ÓÓ:PP` formátumban  
- **Helyszín**: szöveg  
- **Megjegyzés**: szöveg  

---

## 🔄 Rekord módosítása
A felhasználó először kiválasztja, hogyan szeretné az eseményt megkeresni:

1. Név szerint  
2. Dátum szerint  
3. Időpont szerint  
4. Helyszín szerint  
5. Megjegyzés szerint  
6. Összes esemény listázása  

Ezután megadható, melyik mezőt kívánja módosítani:

1. Név  
2. Dátum  
3. Kezdő időpont  
4. Befejező időpont  
5. Helyszín  
6. Megjegyzés  
0. Módosítás befejezése és mentése  

---

## 🗑️ Rekord törlése
- A program kilistáz minden eseményt, mindegyikhez rendel egy számot.  
- A felhasználó kiválasztja a számot.  
- Megerősítés szükséges:  
  - `i` vagy `I` → törlés megtörténik  
  - más válasz → visszalépés a menübe  

---

## 🔍 Események keresése
A keresés típusa a megfelelő szám megadásával választható:

1. Dátum szerint  
2. Időpont szerint  
3. Név szerint  
4. Helyszín szerint  
5. Megjegyzés szerint  

👉 Szöveges mezőknél **részleges keresést** is végez a program.  
Például: ha a felhasználó `Zala` szót adja meg, akkor a **Zalaegerszeg** is találat lesz.

---

## 📅 Események listázása
A felhasználó 3 nézet közül választhat:

1. Napi nézet  
2. Heti nézet  
3. Havi nézet  

Ha nincs esemény, a program ezt is jelzi.

---

## 🚪 Kilépés
A kilépés opció választásakor:  

- a program elköszön a felhasználótól  
- egy billentyű lenyomásával a program bezárul  

---

## ⚠️ Hibakezelés
A program kezeli a hibás választásokat és formátumokat is, így a felhasználó mindig visszakerül a menübe.
