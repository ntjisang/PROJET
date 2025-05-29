#ifndef COMPAREHACH_H
#define COMPAREHACH_H
class HashFunction {
public:
    virtual int hash(const QString &cle, int nmaxe) = 0;
};

class HashFunction1 : public HashFunction {
public:
    int hash(const QString &cle, int nmaxe) override {
         int hash = 0;
        for (int i = 0; i < cle.length(); ++i) {
            hash = 31 * hash + cle[i].unicode();
        }
        return hash % nmaxe;
    }
};

class HashFunction2 : public HashFunction {
public:
    int hash(const QString &cle, int nmaxe) override {
         int hash = 0;
        for (int i = 0; i < cle.length(); ++i) {
            hash = 65599 * hash + cle[i].unicode();
        }
        return hash % nmaxe;
    }
};


class HashFunction3 : public HashFunction {
public:
    int hash(const QString &cle, int nmaxe) override {
         int hash = 0;
        for (int i = 0; i < cle.length(); ++i) {
            hash = hash ^ ((hash << 5) + cle[i].unicode() + (hash >> 2));
        }
        return hash % nmax;
    }
};


QString generateRandomKey(int tailleS) {
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    QString randomString;
    for(int i=0; i<tailleS; ++i) {
        int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
        randomString.append(possibleCharacters.at(index));
    }
    return randomString;
}

QVector<int> testHashFunction(HashFunction *hashFunction, int tableSize, int numKeys) {
    QVector<int> hashTable(tableSize, 0);
    for(int i = 0; i < numKeys; ++i) {
        QString key = generateRandomKey(10); // Génère une clé aléatoire de 10 caractères
        int hashValue = hashFunction->hash(key, tableSize);
        hashTable[hashValue]++;
    }
    return hashTable;
}

#endif // COMPAREHACH_H
