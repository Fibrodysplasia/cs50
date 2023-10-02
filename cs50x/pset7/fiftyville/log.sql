-- Keep a log of any SQL queries you execute as you solve the mystery.

-- The theft occurred on July 28, 2021 on Humphrey Street


-- what are we working with?
-- .tables
-- .schema crime_scene_reports

-- 1. Let's get reports from that day

-- SELECT *
-- FROM crime_scene_reports csr
-- WHERE csr.year = 2021 AND csr.month = 7 AND csr.day = 28 
-- AND csr.street = 'Humphrey Street';

-- Output:
-- 295|2021|7|28|Humphrey Street|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- 297|2021|7|28|Humphrey Street|Littering took place at 16:36. No known witnesses.

-- 2. Let's get interviews:

-- .schema interviews

-- SELECT i.id, i.name, i.transcript
-- FROM interviews i
-- WHERE i.year = 2021 AND i.month = 7 AND i.day = 28;

-- Output:
-- 158|Jose|“Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- 159|Eugene|“I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- 160|Barbara|“You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
-- 161|Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 163|Raymond|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- 191|Lily|Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.

-- So within 10 minutes of the theft (10:05 - 10:25 am), the thief drove out of the bakery parking lot.
-- Prior to 10:05 am, the thief was at the ATM on Leggett Street.
-- During the time frame the thief was leaving the bakery, they called someone for <1 minute and said they were catching the earliest flight the next day (July 29, 2021).

-- 3. Let's go in chronological order:

-- 3a. ATM on Leggett Street
-- .schema atm_transactions

-- SELECT t.id, t.account_number, t.transaction_type, t.amount
-- FROM atm_transactions t
-- where t.year = 2021 AND t.month = 7 AND t.day = 28 AND t.atm_location = 'Leggett Street';

-- Output:
-- 246|28500762|withdraw|48
-- 264|28296815|withdraw|20
-- 266|76054385|withdraw|60
-- 267|49610011|withdraw|50
-- 269|16153065|withdraw|80
-- 275|86363979|deposit|10
-- 288|25506511|withdraw|20
-- 313|81061156|withdraw|30
-- 336|26013199|withdraw|35

-- 3b. Phone calls
-- .schema phone_calls

-- SELECT p.caller, p.receiver
-- FROM phone_calls p
-- WHERE p.year = 2021 AND p.month = 7 AND p.day = 28 AND p.duration < 60;


-- Ouput:
-- (130) 555-0289|(996) 555-8899
-- (499) 555-9472|(892) 555-8872
-- (367) 555-5533|(375) 555-8161
-- (499) 555-9472|(717) 555-1342
-- (286) 555-6063|(676) 555-6554
-- (770) 555-1861|(725) 555-3243
-- (031) 555-6622|(910) 555-3251
-- (826) 555-1652|(066) 555-9701
-- (338) 555-6650|(704) 555-2131

-- 3c Bakery Parking lot
-- .schema bakery_security_logs

-- SELECT b.license_plate
-- FROM bakery_security_logs b
-- WHERE b.year = 2021 AND b.month = 7 AND b.day = 28 AND b.hour = 10 AND b.minute BETWEEN 5 AND 25;

-- Output: (apparently this bakery is crazy busy)
-- R3G7486
-- 13FNH73
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- 3d. Flight and People information
-- .schema flights
-- .schema airports
-- .schema passengers
-- .schema people

-- SELECT p.name, a.city, f.hour, f.minute
-- FROM people p
-- JOIN passengers p2 ON p.passport_number = p2.passport_number
-- JOIN flights f ON p2.flight_id = f.id
-- JOIN airports a ON f.origin_airport_id = a.id
-- WHERE a.city = 'Fiftyville' AND f.year = 2021 AND f.month = 7 AND f.day = 29
-- ORDER BY f.hour ASC LIMIT 10;

-- Output:
-- Doris|Fiftyville|8|20
-- Sofia|Fiftyville|8|20
-- Bruce|Fiftyville|8|20
-- Edward|Fiftyville|8|20
-- Kelsey|Fiftyville|8|20
-- Taylor|Fiftyville|8|20
-- Kenny|Fiftyville|8|20
-- Luca|Fiftyville|8|20
-- Daniel|Fiftyville|9|30
-- Carol|Fiftyville|9|30

-- 4. Put it all together


-- Here we just use elimination at each step until we get to the thief
-- TODO: Come back and rewrite this with joins so it looks better

-- SELECT p.name AS thief
-- FROM people p
-- WHERE p.license_plate IN (
--     SELECT s.license_plate
--     FROM bakery_security_logs s
--     WHERE s.year = 2021 AND s.month = 7 AND s.day = 28 AND s.hour = 10 AND s.minute BETWEEN 5 AND 25
-- ) AND p.id IN (
--     SELECT bank.person_id
--     FROM bank_accounts bank
--     WHERE bank.account_number IN (
--         SELECT atm.account_number
--         FROM atm_transactions atm
--         WHERE atm.year = 2021 AND atm.month = 7 AND atm.day = 28 AND atm.atm_location = 'Leggett Street'
--     )
-- ) AND p.phone_number IN (
--     SELECT c.caller
--     FROM phone_calls c
--     WHERE c.year = 2021 AND c.month = 7 AND c.day = 28 AND c.duration < 60
-- ) AND p.passport_number IN (
--     SELECT pass.passport_number
--     FROM passengers pass
--     WHERE pass.flight_id IN (
--         SELECT f.id
--         FROM flights f
--         WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
--         ORDER BY f.hour ASC, f.minute ASC LIMIT 1
--     )
-- );

-- Output: 
-- Bruce

-- 5. Who did Bruce call?
-- SELECT p.phone_number
-- FROM people p
-- WHERE p.name = 'Bruce';

-- -- Output:
-- (367) 555-5533

-- SELECT p.name AS accomplice
-- FROM people p
-- JOIN phone_calls c ON c.caller = '(367) 555-5533'
-- WHERE c.year = 2021 
-- AND c.month = 7 
-- AND c.day = 28 
-- AND c.duration < 60 
-- AND p.phone_number = c.receiver;

-- Output:
-- Robin

-- 6. Where did he go?

-- SELECT passport_number
-- FROM people
-- WHERE name = 'Bruce';

-- passport: 5773159633

-- Let's get the destination for that flight
-- SELECT a.city as destination
-- FROM airports a
-- JOIN flights f ON f.destination_airport_id = a.id
-- JOIN passengers p ON p.flight_id = f.id
-- WHERE p.passport_number = 5773159633 AND f.year = 2021 AND f.month = 7 AND f.day = 29;