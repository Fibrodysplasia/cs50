-- SELECT name 
-- FROM people 
-- WHERE id IN(SELECT person_id 
--             FROM stars 
--             WHERE movie_id 
--             IN(SELECT id 
--             FROM movies 
--             WHERE title = 'Toy Story'));

SELECT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE m.title = 'Toy Story';