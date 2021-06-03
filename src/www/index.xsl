<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html" doctype-system="about:legacy-compat" encoding="UTF-8" indent="yes"/>

    <xsl:include href="www/_layout.xsl"/>

    <xsl:template match="/">
        <html>
            <xsl:call-template name="header">
                <xsl:with-param name="title" select="'Examples'"/>
                <xsl:with-param name="css" select="'index.css'"/>
            </xsl:call-template>
            <body>
                <h1>List of examples</h1>
                <a href="/login.xslhtml">Login App</a><br/>
                <a href="/todo.xslhtml">Todo App</a><br/>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
