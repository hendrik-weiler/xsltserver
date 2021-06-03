<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html" doctype-system="about:legacy-compat" encoding="UTF-8" indent="yes"/>

    <xsl:include href="www/_layout.xsl"/>

    <xsl:template match="/">
        <html>
            <xsl:call-template name="header">
                <xsl:with-param name="title" select="'The login'"/>
                <xsl:with-param name="css" select="'login.css'"/>
            </xsl:call-template>
            <body>
                <div class="container">
                    <form method="post" action="/login.xslhtml">
                        <p>Login to continue</p>
                        <label for="user">Username</label>
                        <input value="test" type="text" maxlength="60" name="user" id="user" /><br/>
                        <label for="user">Password</label>
                        <input value="abc123" type="password" maxlength="60" name="password" id="password" /><br/>
                        <button class="button" type="submit">Login</button>
                    </form>
                    <xsl:if test="/Data/QueryParams/error = 'true'">
                        <div class="error">
                            Username or password is invalid.
                        </div>
                    </xsl:if>
                </div>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
