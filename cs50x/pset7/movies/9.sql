SELECT p.name
FROM people p
JOIN movies m ON m.year = 2004
JOIN stars s ON m.id = s.movie_id
WHERE p.id = s.person_id
ORDER BY p.birth DESC;