// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#import <SavingController.h>

@implementation SavingController

-(id)init
{
    return [super initWithWindowNibName:@"SavingView"];
}

-(void)awakeFromNib
{
    [progress startAnimation:self];
}

@end
