USE [KGCA_SAMPLE]
GO
/****** Object:  StoredProcedure [dbo].[usp_Test]    Script Date: 10/26/2018 15:38:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER PROCEDURE [dbo].[usp_Test]
AS
	SELECT * FROM dbo.user_list;
