<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html" doctype-system="about:legacy-compat" encoding="UTF-8" indent="yes"/>

    <xsl:include href="www/_layout.xsl"/>

    <xsl:template match="/">
        <html>
            <xsl:call-template name="header">
                <xsl:with-param name="title" select="'Todo List'"/>
                <xsl:with-param name="css" select="'todo.css'"/>
            </xsl:call-template>
            <body>
                <div class="container">
                    <h1>Basic To-Do App</h1>
                    <table>
                        <tr>
                            <th align="left">To-Do's</th>
                            <th align="right">
                                <a href="?removeAll=1">Delete all</a>
                            </th>
                        </tr>
                        <xsl:for-each select="/Data/Entry">
                            <tr>
                                <td><xsl:value-of select="Text"></xsl:value-of></td>
                                <td align="right"><a href="?remove={position()-1}">Delete</a></td>
                            </tr>
                        </xsl:for-each>
                        <xsl:if test="count(/Data/Entry) = 0">
                            <tr>
                                <td colspan="2" align="center">No entries available</td>
                            </tr>
                        </xsl:if>
                    </table>
                    <form class="newentry" method="post" action="">
                        <input placeholder="What needs to be done..." type="text" maxlength="120" name="text" id="text" /><br/>
                        <input class="button" name="addButton" type="submit" value="Add"></input>
                    </form>
                    <xsl:if test="/Data/QueryParams/error = '1'">
                        <div class="error">
                            The textfield cant be empty.
                        </div>
                    </xsl:if>
                </div>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
