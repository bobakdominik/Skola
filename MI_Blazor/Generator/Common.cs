using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Serialization;
using Bogus.Bson;
using Bogus.DataSets;
using static Generator.Common;
using System.Collections;
using System.Text;

namespace Generator
{
    public class Common
    {
        private static readonly Random _rnd = new Random();
        private static readonly string[] _psc = new string[]
        {
            "841 01",
            "917 01",
            "949 01",
            "911 01",
            "974 01",
            "010 01",
            "080 01",
            "040 00",
            "976 57",
            "023 14"
        };

        public static Random RND => _rnd;
        public static string[] PSC => _psc;

        public static DateTime RandomDay()
        {
            DateTime start = new DateTime(1960, 1, 1);
            int range = (DateTime.Today - start).Days;
            return start.AddDays(_rnd.Next(range));
        }

        public static DateTime RandomDayWithHoursMinutesSeconds()
        {           
            DateTime start = new DateTime(1960, 1, 1);
            TimeSpan timeSpan = DateTime.Today - start;
            TimeSpan newSpan = new TimeSpan(0, _rnd.Next(0, (int)timeSpan.TotalMinutes), 0);
            DateTime newDate = start + newSpan;

            return newDate;
        }


        public static DateTime RandomDay(int startYear, bool add = true)
        {
            DateTime start = new DateTime(startYear, 1, 1);
            int range = (DateTime.Today - start).Days;
            var res = add ? start.AddDays(_rnd.Next(range)) : start.AddDays(-_rnd.Next(range));
            return res;
        }

        public static DateTime RandomDay(int startYear, int startMonth, int startDay, bool add = true)
        {
            DateTime start = new DateTime(startYear, startMonth, startDay);
            int range = (DateTime.Today - start).Days;
            var res = add ? start.AddDays(_rnd.Next(range)) : start.AddDays(-_rnd.Next(range));
            return res;
        }

        public static string RandomDigits(int length)
        {
            var random = new Random();
            string s = random.Next(1,10).ToString();
            for (int i = 0; i < length - 1; i++)
                s = String.Concat(s, random.Next(10).ToString());
            return s;
        }

        public static int RandomPercentage()
        {
            var random = new Random();
            int p = random.Next(1, 100);
            
            return p;
        }

        public static int RandomMinMax(int min, int max)
        {
            var random = new Random();
            int rand_num = random.Next(min, max);

            return rand_num;
        }

        public static DateTime GetDateFromRodCislo(string rodCislo)
        {
            var year = rodCislo[..2];
            year = Convert.ToInt32(year) > Convert.ToInt32(DateTime.Now.ToString("yy")) ? "19" + year : "20" + year;
            var month = (Convert.ToInt32(rodCislo.Substring(2, 2)) % 50).ToString();
            if (month.Length == 1)
            {
                month = "0" + month;
            }
            var day = rodCislo.Substring(4, 2);
            return DateTime.ParseExact(string.Format("{0}.{1}.{2}", day, month, year), "dd.MM.yyyy",
                                           System.Globalization.CultureInfo.InvariantCulture);
        }  
    }   
}
