﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Catrobat.TestsCommon.Misc
{
    public static class XmlDocumentCompare
    {
        public static void Compare(XDocument expected, XDocument actual)
        {
            var expectedElements = expected.Elements().ToArray();
            var actualElements = actual.Elements().ToArray();

            Assert.AreEqual(expectedElements.Count(), actualElements.Count());

            for (int i = 0; i < expectedElements.Count(); i++)
            {
                CompareElement(expectedElements[i], actualElements[i]);
            }
        }

        private static void CompareElement(XElement expectedElement, XElement actualElement)
        {
            Assert.AreEqual(expectedElement.Name, actualElement.Name);

            var expectedAttributes = expectedElement.Attributes().ToArray();
            var actualAttributes = actualElement.Attributes().ToArray();

            //Assert.AreEqual(expectedAttributes.Count(), actualAttributes.Count());

            for (int i = 0; i < expectedAttributes.Count(); i++)
            {
                Assert.AreEqual(expectedAttributes[i].Name, actualAttributes[i].Name);
            }

            var expectedElements = expectedElement.Elements().ToArray();
            var actualElements = actualElement.Elements().ToArray();

            for (int i = 0; i < expectedElements.Count(); i++)
            {
                CompareElement(expectedElements[i], actualElements[i]);
            }
        }
    }
}
