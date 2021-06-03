<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">


    <xsl:template name="header">
        <xsl:param name="title"/>
        <xsl:param name="css"/>
        <head>
            <title><xsl:value-of select="$title"></xsl:value-of></title>
            <link rel="stylesheet" href="/_base.css" />
            <link rel="stylesheet" href="{$css}" />
        </head>
    </xsl:template>

</xsl:stylesheet>