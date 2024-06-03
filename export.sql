--------------------------------------------------------
--  File created - Wednesday-April-05-2023   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table COMPTABILITE
--------------------------------------------------------

  CREATE TABLE "COMPTABILITE" ("ID" NUMBER(30,0), "TYPE" VARCHAR2(20), "MONTANT" NUMBER(20,0), "DATER" DATE, "ID_MAT" NUMBER)
--------------------------------------------------------
--  DDL for Table DONS
--------------------------------------------------------

  CREATE TABLE "DONS" ("ID" NUMBER(30,0), "TYPE" VARCHAR2(20), "ETAT" VARCHAR2(20), "ID_COMPT" NUMBER, "NOM" VARCHAR2(20), "DATER" DATE)
--------------------------------------------------------
--  DDL for Table MATERIEL
--------------------------------------------------------

  CREATE TABLE "MATERIEL" ("ID" NUMBER(30,0), "TYPE" VARCHAR2(20), "FRAIS" NUMBER(20,0), "QUANTITE" NUMBER)
--------------------------------------------------------
--  DDL for Table SDF
--------------------------------------------------------

  CREATE TABLE "SDF" ("ID" NUMBER(30,0), "NOM" VARCHAR2(20), "PRENOM" VARCHAR2(20), "DN" DATE, "ETAT" VARCHAR2(20), "BESOIN" VARCHAR2(20))
--------------------------------------------------------
--  DDL for Table SERVICES
--------------------------------------------------------

  CREATE TABLE "SERVICES" ("ID" NUMBER(30,0), "TYPE" VARCHAR2(20), "NOM" VARCHAR2(20), "LOCATION" VARCHAR2(20))
--------------------------------------------------------
--  DDL for Index COMPTABILITE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "COMPTABILITE_PK" ON "COMPTABILITE" ("ID")
--------------------------------------------------------
--  DDL for Index MATERIEL_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "MATERIEL_PK" ON "MATERIEL" ("ID")
--------------------------------------------------------
--  DDL for Index SDF_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "SDF_PK" ON "SDF" ("ID")
--------------------------------------------------------
--  DDL for Index DONS_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DONS_PK" ON "DONS" ("ID")
--------------------------------------------------------
--  DDL for Index SERVICES_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "SERVICES_PK" ON "SERVICES" ("ID")
--------------------------------------------------------
--  DDL for Trigger COMPTABILITE_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "COMPTABILITE_TRG" 
BEFORE INSERT ON COMPTABILITE 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    NULL;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "COMPTABILITE_TRG" ENABLE
--------------------------------------------------------
--  DDL for Trigger COMPTABILITE_TRG1
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "COMPTABILITE_TRG1" 
BEFORE INSERT ON COMPTABILITE 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID IS NULL THEN
      SELECT COMPTABILITE_SEQ1.NEXTVAL INTO :NEW.ID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "COMPTABILITE_TRG1" ENABLE
--------------------------------------------------------
--  DDL for Trigger DONS_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "DONS_TRG" 
BEFORE INSERT ON DONS 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    NULL;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "DONS_TRG" ENABLE
--------------------------------------------------------
--  DDL for Trigger DONS_TRG1
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "DONS_TRG1" 
BEFORE INSERT ON DONS 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID IS NULL THEN
      SELECT DONS_SEQ1.NEXTVAL INTO :NEW.ID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "DONS_TRG1" ENABLE
--------------------------------------------------------
--  DDL for Trigger SERVICES_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "SERVICES_TRG" 
BEFORE INSERT ON SERVICES 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID IS NULL THEN
      SELECT SERVICES_SEQ.NEXTVAL INTO :NEW.ID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "SERVICES_TRG" ENABLE
--------------------------------------------------------
--  Constraints for Table MATERIEL
--------------------------------------------------------

  ALTER TABLE "MATERIEL" ADD CONSTRAINT "MATERIEL_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "MATERIEL" MODIFY ("ID" NOT NULL ENABLE)
--------------------------------------------------------
--  Constraints for Table COMPTABILITE
--------------------------------------------------------

  ALTER TABLE "COMPTABILITE" ADD CONSTRAINT "COMPTABILITE_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "COMPTABILITE" MODIFY ("ID" NOT NULL ENABLE)
--------------------------------------------------------
--  Constraints for Table SDF
--------------------------------------------------------

  ALTER TABLE "SDF" ADD CONSTRAINT "SDF_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "SDF" MODIFY ("ID" NOT NULL ENABLE)
  ALTER TABLE "SDF" MODIFY ("NOM" NOT NULL ENABLE)
  ALTER TABLE "SDF" MODIFY ("PRENOM" NOT NULL ENABLE)
--------------------------------------------------------
--  Constraints for Table SERVICES
--------------------------------------------------------

  ALTER TABLE "SERVICES" ADD CONSTRAINT "SERVICES_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "SERVICES" MODIFY ("ID" NOT NULL ENABLE)
--------------------------------------------------------
--  Constraints for Table DONS
--------------------------------------------------------

  ALTER TABLE "DONS" ADD CONSTRAINT "DONS_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "DONS" MODIFY ("ID" NOT NULL ENABLE)
