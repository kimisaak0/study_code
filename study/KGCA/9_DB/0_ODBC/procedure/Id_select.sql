CREATE PROCEDURE [dbo].[usp_Select]
	@UID NCHAR(10)
AS
	SELECT * FROM dbo.user_list
	WHERE UID = Client_ID;
RETURN 0
