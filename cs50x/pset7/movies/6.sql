-- SELECT AVG(rating) 
-- FROM ratings 
-- WHERE movie_id 
-- IN (SELECT id 
--     FROM movies 
--     WHERE year = 2012);

SELECT AVG(rating)
FROM ratings r
JOIN movies m ON r.movie_id = m.id
WHERE m.year = 2012;