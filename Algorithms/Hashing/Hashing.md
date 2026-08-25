**What is Hashing?**

Using mathematical formulas to transform messages into fixed length, deterministic strings

**Purpose** Has the original message changed since it was hashed ?

  

$$ Message \xrightarrow{Hashing} Digest $$

Digest is also known as a Hash / Checksum / Fingerprint / CRC, etc



### Hash Functions or Algorithms

Functions used to map data of an arbitrary size to return data of fixed size

A hash function takes some string and coverts it into a fixed length string.
Hash functions are pseudo-random

Cryptographic Hash Function
- Deterministic
- Fast
- Irreversible
- Utilize the Avalanche effect
- Collision resistant

Takeaways
- Pre-image resistance
- Second pre-image resistance
- unbreakable without sing a brute force approach
- one-way  

Practical Uses
- Verifying file and message integrity
- File and Data identification (Git)
- Password Verification
  

**Rules**

1. **It must be deterministic**
same input always has the same output

2. **Fixed Length Output**
for all possible inputs

3. **Irreversible Output**


examples:

```

Legacy: MD5, SHA1

Modern: SHA224, SHA256, SHA384, SHA512

Future: SHA3-224, SHA3-256, SHA3-384, SHA3-512

```


### Hash Collisions

Collision refers to two messages resulting in identical digests
Cannot be avoid as they are byproduct of "fixed width digests"
Can only be made more rare


Ref: Birthday Paradox, Pigeonhole Principle


###  Data Integrity - How Hashing is used to ensure data isn't modified - HMAC

Message Authentication Code (MAC)
- Concept of combining a message with a secret key before hashing

**Purpose**
- Detect unauthorized alteration of message & digest 
- Only whoever has the acceptable key can create an acceptable digest
- Integration and Authentication of bulk data

Challenges: Key-Exchange problem

Industry Standard Specification of combining message and key
- HMAC (Hash Based Message Authentication Code) RFC 2104


Other examples:

```
Legacy: (none in significant use)

Modern: HMAC, Poly1305

Future: GCM, CCM, (AEAD Ciphers)
```


### Hashing Algorithms Examples

Real World Hashing Algorithms must satisfy four requirements
1. Infeasible to produce a given digest
2. Impossible to extract original message
3. Slight changes produce drastic differences
4. Resulting digest is fixed width

uses : Message Authentication, Digital Signatures

#### djb2 - simple hashing algorithm
https://theartincode.stanis.me/008-djb2/

Variable Length Output Function

#### MD5 Message-Digest Algorithm
https://www.ietf.org/rfc/rfc1321.txt

MD5 Function takes a 512 bits input and returns a pseudorandom 128 bits output
It operates on 32 bit chucks (words)

Starts with a hardcoded 128 bit value called as a internal state and it updates as the algorithm runs and returns it in the end

#### SHA : Secure Hashing Algorithm
