<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html" doctype-system="about:legacy-compat" encoding="UTF-8" indent="yes"/>

    <xsl:include href="www/_layout.xsl"/>

    <xsl:template name="navPoint">
        <xsl:param name="label"></xsl:param>
        <xsl:param name="page"></xsl:param>
        <xsl:param name="condition"></xsl:param>
        <xsl:if test="$condition">
            <a class="active" href="?page={$page}"><xsl:value-of select="$label"></xsl:value-of></a>
        </xsl:if>
        <xsl:if test="not($condition)">
            <a href="?page={$page}"><xsl:value-of select="$label"></xsl:value-of></a>
        </xsl:if>
    </xsl:template>

    <xsl:variable name="isInHome" select="/Data/QueryParams/page = 'home' or not(/Data/QueryParams/page)"></xsl:variable>

    <xsl:template match="/">
        <html>
            <xsl:call-template name="header">
                <xsl:with-param name="title" select="'The app'"/>
                <xsl:with-param name="css" select="'index.css'"/>
            </xsl:call-template>
            <body>
                <div class="left">
                    <ul>
                        <li>
                            <xsl:call-template name="navPoint">
                                <xsl:with-param name="label" select="'Home'"/>
                                <xsl:with-param name="page" select="'home'"/>
                                <xsl:with-param name="condition" select="$isInHome"/>
                            </xsl:call-template>
                            <xsl:call-template name="navPoint">
                                <xsl:with-param name="label" select="'Table'"/>
                                <xsl:with-param name="page" select="'table'"/>
                                <xsl:with-param name="condition" select="/Data/QueryParams/page = 'table'"/>
                            </xsl:call-template>
                        </li>
                    </ul>
                    <form method="post" action="">
                        <input class="button" value="Logout" name="doLogout" type="submit" />
                    </form>
                </div>
                <main class="content">
                    <xsl:choose>
                        <xsl:when test="$isInHome">
                            <div class="outer-container">
                                <div class="inner-container">This is a example page.</div>
                            </div>
                        </xsl:when>
                        <xsl:when test="/Data/QueryParams/page = 'table'">
                            <h1>Table example</h1>
                            <table>
                                <tr>
                                    <th>Name</th>
                                    <th style="text-align:right;">Age</th>
                                </tr>
                                <xsl:for-each select="/Data/Person">
                                    <tr>
                                        <td><xsl:value-of select="Name"></xsl:value-of></td>
                                        <td align="right"><xsl:value-of select="Age"></xsl:value-of></td>
                                    </tr>
                                </xsl:for-each>
                                <tr>
                                    <td align="right" colspan="2">
                                        <strong>
                                            Age summary:
                                            <xsl:value-of select="sum(/Data/Person/Age)"></xsl:value-of>
                                        </strong>
                                    </td>
                                </tr>
                            </table>
                        </xsl:when>
                        <xsl:otherwise>
                            <div class="outer-container">
                                <div class="inner-container">There is no page with this name.</div>
                            </div>
                        </xsl:otherwise>
                    </xsl:choose>
                </main>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
