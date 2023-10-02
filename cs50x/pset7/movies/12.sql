SELECT m.title
FROM movies m
JOIN stars s ON m.id = s.movie_id
JOIN people p on s.person_id = p.id
WHERE p.name IN('Bradley Cooper', 'Jennifer Lawrence');
