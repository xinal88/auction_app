-- Create role if it doesn't exist, or alter if it does
DO $$
BEGIN
    IF NOT EXISTS (SELECT FROM pg_roles WHERE rolname = 'trung') THEN
        CREATE ROLE trung WITH LOGIN SUPERUSER PASSWORD '123';
    ELSE
        ALTER ROLE trung WITH PASSWORD '123';
    END IF;
END
$$;
